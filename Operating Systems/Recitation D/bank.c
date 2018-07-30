#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>
#include <errno.h>

#define FIFO_NAME1 "ATM1"
#define FIFO_NAME2 "ATM2" 


void main(int argc, char *argv[])
{
	int TOTAL = 0;
	int adder;
	int fd1, fd2, res;
	
	if (access(FIFO_NAME1, F_OK) == -1) 
	{ // check if fifo already exists
		res = mkfifo(FIFO_NAME1, 0777); // if not then, create the fifo
		if (res != 0) 
		{
			fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME1);
			exit(0);
		}
	}
	
	if (access(FIFO_NAME2, F_OK) == -1) 
        { // check if fifo already exists
                res = mkfifo(FIFO_NAME2, 0777); // if not then, create the fifo
                if (res != 0) 
                {
                        fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME2);
                        exit(0);
                }
        }

	while(1)
	{
		
		fd1 = open(FIFO_NAME1, O_RDWR | O_NONBLOCK);
		fd2 = open(FIFO_NAME2, O_RDWR | O_NONBLOCK);

		fd_set fds;
  		int maxfd;
  		char buf[256];
		int n;
		ssize_t bytes;
		size_t total_bytes;

		for (;;) 
		{
			FD_ZERO(&fds); // Clear FD set for select
                	FD_SET(fd1, &fds);
                	FD_SET(fd2, &fds);
			n = select(FD_SETSIZE, &fds, NULL, NULL, NULL);
        		
			if (!n)
            			continue;
        		if (n == -1) {
            			perror("select");
            			//return EXIT_FAILURE;
        		}
        		
			//AT1
			if (FD_ISSET(fd1, &fds)) 
			{
            			//printf("Descriptor %d is ready.\n", fd1);
            			total_bytes = 0;
            			for(;;) 
				{
                			bytes = read(fd1, buf, sizeof(buf));
                			if (bytes > 0) 
					{
                    				total_bytes += (size_t)bytes;
						sscanf(buf, " %d", &adder);
                			} 
					else 
					{
                    				if (errno == EWOULDBLOCK) 
						{
                        				/* Done reading */
                        				//printf("done reading (%lu bytes)\n", total_bytes);  
							TOTAL = TOTAL + adder;
                                                	printf("Your new total is: $%d\n", TOTAL);
							break;
                    				} 
						else 
						{
                        				perror("read");
                      	 				//return EXIT_FAILURE;
                    				}
             				}
          			}
        		}

			FD_ZERO(&fds); //Clear and set again
			FD_SET(fd1, &fds);
                	FD_SET(fd2, &fds);
			n = select(FD_SETSIZE, &fds, NULL, NULL, NULL);
			
			//ATM2
			if (FD_ISSET(fd2, &fds))
                        {
                                //printf("Descriptor %d is ready.\n", fd2);
                                total_bytes = 0;
                                for(;;)
                                {
                                        bytes = read(fd2, buf, sizeof(buf));
                                        if (bytes > 0)
                                        {
                                                total_bytes += (size_t)bytes;
                                                sscanf(buf, " %d", &adder);
                                        }
                                        else
                                        {
                                                if (errno == EWOULDBLOCK)
                                                {
                                                        /* Done reading */
                                                       // printf("done reading (%lu bytes)\n", total_bytes);
                                                        TOTAL = TOTAL + adder;
                                                        printf("Your new total is: $%d\n", TOTAL);
                                                        break;
                                                }
                                                else
                                                {
                                                        perror("read");
                                                        //return EXIT_FAILURE;
                                                }
                                        }
                                }
                        }
    		}          
	}
}
