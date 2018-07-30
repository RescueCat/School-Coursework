#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#define BLKSIZE 1024


void main (int argc, char *argv[])
{
	//Less than/more than the aloud amount of arguments
	if(argc < 3 || argc > 4)
	{
		printf("Not enough or too many arguments.\n");
		printf("This program takes in at least 3 arguments, and at most 4 arguments. \n");
		return;
	}
	
	//Variables for Reading from Standard In '-'
	int k, dashcount = 5;
	char *filename;
	char *comp = "-";

	//Variables for reading writing
	int i;
	char buf[BLKSIZE];
        int bytesread, byteswritten;

	//Get file from standard in if '-'
	for(k = 1; k < argc; k++)
        {
                if(*comp == *argv[k])
                {
                        read(STDIN_FILENO, filename, 200);
			if(filename < 0)
			{
				printf("%s cannot be created as a file.\n", filename);
				return;
			}
			strtok(filename, "\n");
			argv[k] = filename;
			dashcount++;        
		}
        }
	printf("%s %s %s \n" ,argv[0], argv[1], argv[2]);
	//Error Reporting for More than one Dash '-'
	if(dashcount > 6)
	{
		printf("More than one '-', incorrect usage.\n");
		return;
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
				return;
			}
			while((bytesread = read(fd,buf,BLKSIZE)) > 0)
			{
				write(STDOUT_FILENO, buf, bytesread);
				if(buf < 0)
				{
					printf("Cannot write to standard out.\n");			
					return;
				}
			}
			close(fd);
			if(fd < 0)
			{
				printf("Cannot close file.");
				return;
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
			return;
		}
		for(i = 1; i < argc - 1; i++)
		{
			int fd = open(argv[i], O_RDONLY);
			if(fd < 0)
			{
				perror(argv[i]);
				return;
			}
			while((bytesread = read(fd, buf, BLKSIZE)) > 0)
			{
				write(gwrit, buf, bytesread);
				if(buf < 0)
				{
					printf("Cannot write to file %s.\n", argv[i]);
					return;
				}
			}
			close(fd);
			if(fd < 0)
			{
				printf("Cannot close file %s.", argv[i]);
				return;
			}
		}
		close(gwrit);
		if(gwrit < 0)
		{
			perror(argv[argc-1]);
			return;
		}
	}
}
