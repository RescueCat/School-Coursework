#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
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
        char *comp = "-";
        filename = (char *)malloc(200 * sizeof(char));

        
	//Variables for reading writing
        int i, n, j;
        char buf1[BLKSIZE];
        char buf2[BLKSIZE];
        int bytesread, byteswritten;
        int tobreak = 5;

        //Get file from standard in if '-'
        for(k = 1; k < argc; k++)
        {
                if(*comp == *argv[k])
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
                int fd = open(argv[1],O_RDWR);
		if(fd < 0)
                {
                        perror(argv[1]);
                        exit(0);
                }

                int fs = open(argv[2],O_RDWR);
                if(fs < 0)
                {
                        perror(argv[2]);
                        exit(0);
                }
        
                while((n = read(fd, buf1, 1)) > 0)
                {
		        if(n < 0)
                        {
                        	printf("Cannot read from file %s.\n", argv[1]);
                                exit(0);
                        }
                        write(STDOUT_FILENO, buf1, n);     
			if(buf1 < 0)
			{
				printf("Cannot write to standard out.\n");
				exit(0);
			}      
                        if(buf1[0] == '\n')
                        {
                                while((tobreak > 4) && ((j = read(fs, buf2, 1)) > 0))
                                {      
                        		if(j < 0)
                        		{
                                		printf("Cannot read from file %s.\n", argv[2]);
                                		exit(0);
                        		}                  
                                        if (buf2[0] == '\n')
                                        {
                                                tobreak = 1;
                                        }                                             
                                        write(STDOUT_FILENO, buf2,j);                
                        		if(buf1 < 0)
                        		{
                                		printf("Cannot write to standard out.\n");
                                		exit(0);
                        		} 
                                }                                                     
                        }                                                             
                        tobreak = 5;
                }                                                                             
                while((j = read(fs, buf2, BLKSIZE)) > 0)
		{
			if (j < 0)
				perror(argv[2]);
                        write(STDOUT_FILENO, buf2, j);
			if (buf2 < 0)
				perror(argv[2]);
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

                int fd = open(argv[1],O_RDWR);
		if(fd < 0)
                {
                        perror(argv[1]);
                        exit(0);
                }

                int fs = open(argv[2],O_RDWR);
                if(fs < 0)
                {
                        perror(argv[2]);
                        exit(0);
                }


                while((n = read(fd, buf1, 1)) > 0)
                {
			if(n < 0)
				perror(argv[1]);
                        write(gwrit, buf1, n);
			if(buf1 < 0)
				perror(argv[1]);
                        if(buf1[0] == '\n')
                        {
                                while((tobreak > 4) && ((j = read(fs, buf2, 1)) > 0))
                                {
					if(j < 0)
						perror(argv[2]);
                                        if (buf2[0] == '\n')
                                        {
                                                tobreak = 1;
                                        }
                                        write(gwrit, buf2,j);
					if(buf2 < 0)
						perror(argv[2]);
                                }
                        }
                        tobreak = 5;
                }
                while((j = read(fs, buf2, BLKSIZE)) > 0)
		{
                        if (j < 0)
                                perror(argv[2]);
                        write(gwrit, buf2, j);  
                        if (buf2 < 0)
                                perror(argv[2]);              
		}

                close(gwrit);
                if(gwrit < 0)
                {
                        perror(argv[argc-1]);
                        exit(0);
                }
                close(fd);
                if(fd < 0)
                {
                        perror(argv[1]);
                        exit(0);
                }
                close(fs);
                if(fs < 0)
                {
                        perror(argv[2]);
                        exit(0);
                }
        }
}
