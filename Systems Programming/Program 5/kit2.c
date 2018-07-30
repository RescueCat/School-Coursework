#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLKSIZE 1024


void main (int argc, char *argv[])
{
        //Less than/more than the aloud amount of arguments
        if(argc < 3 || argc > 4)
        {
                printf("Not enough or too many arguments.\n");
                printf("This program takes at most 3 arguments and at least 2.\n");
                exit(0);
        }

        //Variables for Reading from Standard In '-'
        int k, dashcount = 5;
        char *filename;
        filename = (char *)malloc(200 * sizeof(char));

        //Variables for reading writing
        int i;
        char buf[BLKSIZE];
        int bytesread, byteswritten;

        //Get file from standard in if '-'
        for(k = 1; k < argc; k++)
        {
                if(strstr(argv[k],"-") != NULL)
                {
                        read(STDIN_FILENO, filename, 200);
                        strtok(filename, "\n");
                        argv[k] = filename;
                        //printf("Read from standard in: %s\n",filename);
                        dashcount++;
                }
        }

        //Error Reporting for More than one Dash '-'
        if(dashcount > 6)
        {
                perror("More than one '-', incorrect usage.\n");
                exit(0);
        }

        //Operation for two arguments
	if(argc < 4)
	{
		for(i = 1; i < argc; i++)
		{
			int fd = open (argv[i],O_RDONLY);
			while((bytesread = read(fd,buf,BLKSIZE)) > 0)
                        	write(STDOUT_FILENO,buf,bytesread);
		}
	}	
	//Operation for three arguments
	else
	{	
		int gwrit = open(argv[argc-1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		for(i = 1; i < argc-1; i++)
		{
			int fd = open (argv[i],O_RDONLY);
			while((bytesread = read(fd,buf,BLKSIZE)) > 0)
				 write(gwrit, buf, bytesread);
		}	
	}
}
