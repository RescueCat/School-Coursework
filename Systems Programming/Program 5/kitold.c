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
		printf("This program takes in at least 3 arguments, and at most 4 arguments. \n");
		exit(0);
	}
	
	//Variables for Reading from Standard In '-'
	int k, dashcount = 5;
	char *filename;

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
			if(filename < 0)
			{
				printf("%s cannot be created as a file.\n", filename);
				exit(0);
			}
			strtok(filename, "\n");
			argv[k] = filename;
			dashcount++;        
		}
        }
	
	//Error Reporting for More than one Dash '-'
	if(dashcount > 6)
	{
		printf("More than one '-', incorrect usage.\n");
		exit(0);
	}
	
	//Operation for two arguments
	if(argc < 4)
	{
		for(i = 1; i < argc; i++)
		{
			int fd = open(argv[i], O_RDONLY);
			if(fd < 0)
			{
				perror(argv[i]);
				exit(0);
			}
			while((bytesread = read(fd,buf,BLKSIZE)) > 0)
			{
				write(STDOUT_FILENO, buf, bytesread);
				if(buf < 0)
				{
					printf("Cannot write to standard out.\n");			
					exit(0);
				}
			}
			close(fd);
			if(fd < 0)
			{
				printf("Cannot close file.");
				exit(0);
			}
		}
	}

	//Operation for three arguments
	else
	{	
		int gwrit = open(argv[argc-1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		if(gwrit < 0)
		{
			perror(argv[argc-1]);
			exit(0);
		}
		for(i = 1; i < argc - 1; i++)
		{
			int fd = open(argv[i], O_RDONLY);
			if(fd < 0)
			{
				perror(argv[i]);
				exit(0);
			}
			while((bytesread = read(fd, buf, BLKSIZE)) > 0)
			{
				write(gwrit, buf, bytesread);
				if(buf < 0)
				{
					printf("Cannot write to file %s.\n", argv[i]);
					exit(0);
				}
			}
			close(fd);
			if(fd < 0)
			{
				printf("Cannot close file %s.", argv[i]);
				exit(0);
			}
		}
		close(gwrit);
		if(gwrit < 0)
		{
			perror(argv[argc-1]);
			exit(0);
		}
	}
}
