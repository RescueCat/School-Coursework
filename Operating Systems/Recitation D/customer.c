#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void main(int argc, char *argv[])
{
	char mesg[1024];
	int res;
        int fd1;
	
	char const* const FIFO_NAME = argv[1];


	mkfifo(FIFO_NAME, 0777); /* Make Pipe*/
        if (res != 0)
        {
        	fprintf(stderr, "Could not create fifo %s\n", argv[1]);
                exit(0);
        }
	
	while(1)
	{
		fd1 = open(argv[1],O_WRONLY);
		printf("Amount you would like to deposit?: ");
		fgets(mesg, 80, stdin);
		fflush(stdin);
		printf("\n");
		write(fd1, mesg, sizeof(mesg));
		close(fd1);

		int value;
		sscanf(mesg, " %d", &value);
		if(value < 0)
		{
			printf("Closing terminal.\n");
			break;
		}
	}

}
