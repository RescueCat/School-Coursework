#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <pthread.h>
#include "restart.h"
#include "uici.h"

pthread_mutex_t* g_mutex;  
void init_mutex(void)  
{  
   	int ret;   
   	g_mutex=(pthread_mutex_t*)mmap(NULL, sizeof(pthread_mutex_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);  
   	if( MAP_FAILED==g_mutex )  
   	{  
      	 	perror("mmap");  
       		exit(1);  
   	}  

   	pthread_mutexattr_t attr;  
   	pthread_mutexattr_init(&attr);  

   	//set mutex process shared 
   	ret=pthread_mutexattr_setpshared(&attr,PTHREAD_PROCESS_SHARED);  
   	if( ret!=0 )  
   	{  
      	 	perror("init_mutex pthread_mutexattr_setpshared");  
       		exit(1);  
   	}  
   	pthread_mutex_init(g_mutex, &attr);  
}  

int main(int argc, char *argv[]) 
{
	//Create Custom Mutex, shared among all processes
	init_mutex();
	int ret;
	
	//Map Balance to Memory and set to 100
	int * Balance = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
   	* Balance = 100;

	int bytescopied;
   	pid_t child;
   	char client[MAX_CANON];
   	int communfd;
   	int listenfd;
   	u_port_t portnumber;
	char MSG[40];
	int AC, NUMP, MIN, MAX, i, DepM;
	pthread_t tid;
 
   	if (argc != 2) 
	{
      		fprintf(stderr, "Usage: %s port\n", argv[0]);
      		return 1;   
   	}  
   	portnumber = (u_port_t) atoi(argv[1]);
   	if ((listenfd = u_open(portnumber)) == -1) 
	{
      		perror("Failed to create listening endpoint");
      		return 1;
   	}
   	fprintf(stderr, "[%ld]: Waiting for connection on port %d\n",
                    (long)getpid(), (int)portnumber);
   	for ( ; ; ) 
	{
      		if ((communfd = u_accept(listenfd, client, MAX_CANON)) == -1) 
		{
         		perror("Failed to accept connection");
         		continue;
      		}
      		fprintf(stderr, "[%ld]:connected to %s\n", (long)getpid(), client);
      		if ((child = fork()) == -1) 
         		perror("Failed to fork a child");
      		if (child == 0) 
		{/* child code */
         		if (r_close(listenfd) == -1) 
			{
            			fprintf(stderr, "[%ld]:failed to close listenfd: %s\n",
                             		(long)getpid(), strerror(errno));
            			return 1;
         		}
			//Read in the Request Message
			r_read(communfd, &MSG, sizeof(MSG));
			
			//Parse the Request Message
			sscanf (MSG,"%d %d %d %d ", &AC, &NUMP, &MIN, &MAX);
			//printf("%d %d %d %d \n", AC, NUMP, MIN, MAX);
			printf("Current Balance is %d \n", *Balance);
			fflush(stdout);

			//Deposite or withdrawal
                        if(AC == 0)//Deposit
                        {
				printf("Making %d deposits . . . \n", NUMP);
                                for(i = 0; i < NUMP; i++)
                                {
                                        r_read(communfd, &MSG, sizeof(MSG));
                                        sscanf(MSG, "%d ", &DepM);
					while((DepM > MAX) || (DepM < MIN))
					{
						printf("%d does not fit min/max req\n", DepM);
						r_read(communfd, &MSG, sizeof(MSG));
                                        	sscanf(MSG, "%d ", &DepM);
					}
	
					//Lock Mutex Critical Section
					pthread_mutex_lock(g_mutex);  
         				
					//Critical Section  
                                        *Balance = (int)*Balance + DepM;
                                        printf("New balance %d \n", (int)*Balance);

					//Unlock Mutex
					pthread_mutex_unlock(g_mutex);
                                }
                        }
                        else //Withdrawal
			{
				printf("Making %d withdrawals . . . \n", NUMP);
                                for(i = 0; i < NUMP; i++)
                                {
                                        r_read(communfd, &MSG, sizeof(MSG));
                                        sscanf(MSG, "%d ", &DepM);
					while((DepM > MAX) || (DepM < MIN))
                                        {
                                                printf("%d does not fit min/max req\n", DepM);
                                                r_read(communfd, &MSG, sizeof(MSG));
                                                sscanf(MSG, "%d ", &DepM);
                                        }
	
					//Lock Mutex Critical Section
                                        pthread_mutex_lock(g_mutex); 

					//Critical Section
                                        *Balance = (int)*Balance - DepM;
                                        printf("New balance %d \n", (int)*Balance);

					//Unlock Mutex
                                        pthread_mutex_unlock(g_mutex);
                                }
                        }
			return 0;
      		}
		r_close(communfd);
      		//while (r_waitpid(-1, NULL, WNOHANG) > 0)  ;         /* clean up zombies */
   	}
}
