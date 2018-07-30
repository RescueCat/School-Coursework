#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_NAME1 "ATM1"
#define FIFO_NAME2 "ATM2" 


void main(int argc, char *argv[])
{
	int TOTAL = 0;
	int adder;
	int res;
	int fd1, fd2;
	char buffer1[1024];
	char buffer2[1024];
	
	
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
	
	//clear strings
	memset(buffer1, '\0', sizeof(buffer1));
	memset(buffer2, '\0', sizeof(buffer2));
	
	while(1)
	{
		//fd1 = open(FIFO_NAME1, O_RDONLY);
		fd2 = open(FIFO_NAME2, O_RDONLY);

		//read(fd1, buffer1, sizeof(buffer1));
		read(fd2, buffer2, sizeof(buffer2));
	
		//sscanf(buffer1, "%d", &adder);
		sscanf(buffer2, "%d", &adder);
		
		TOTAL += adder;

		printf("Your new total is: %d\n", TOTAL);
	
		//close(fd1);
		close(fd2);
	}

	
}
