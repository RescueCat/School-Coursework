#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "restart.h"
#include "uici.h"
 
int main(int argc, char *argv[]) 
{
   	int bytescopied;
   	int communfd;
   	u_port_t portnumber;
   	int AC, NUMOP, MIN, MAX, i; 
	char MSG[40];
	char *DWM;
	char *check;
 
   	if (argc != 7) 
	{
      		fprintf(stderr, "Usage: %s host port\n", argv[0]);
      		return 1;
   	}
	//Parse Commands
   	portnumber = (u_port_t)atoi(argv[2]);
	AC = atoi(argv[3]);
	NUMOP = atoi(argv[4]);
	MIN = atoi(argv[5]);
	MAX = atoi(argv[6]);
	
	//For interface
	if(AC == 0)
		DWM = "deposits";
	else
		DWM = "withdrawals";

	//Create request message to send to server 
	snprintf(MSG, sizeof(MSG), "%d %d %d %d ", AC, NUMOP, MIN, MAX);

   	if ((communfd = u_connect(portnumber, argv[1])) == -1) 
	{
      		perror("Failed to make connection");
      		return 1;
   	}
   
	fprintf(stderr, "[%ld]:connected %s\n", (long)getpid(), argv[1]);
	r_write(communfd, MSG, sizeof(MSG));
	printf("You can make up to %d %s (press enter twice when done): \n", NUMOP, DWM);
   	bytescopied = copyfile(STDIN_FILENO, communfd);
   	printf("Thank you for your business. \n");
}
