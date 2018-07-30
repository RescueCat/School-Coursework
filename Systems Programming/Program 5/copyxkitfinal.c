#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
//#include <stdlib.h>
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
        int i, n, j;
        char buf1[BLKSIZE];
        char buf2[BLKSIZE];
        int bytesread, byteswritten;
        int tobreak = 5;
 //       filename = (char *)malloc(200 * sizeof(char));

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

        //Error Reporting for More than one Dash '-'
        if(dashcount > 6)
        {
                printf("More than one '-', incorrect usage.\n");
                return;
        }

        printf("%s %s %s \n", argv[0], argv[1], argv[2]);

        //Operation for two arguments
        if(argc < 4)
        {
                int fd = open(argv[1],O_RDWR);
                int fs = open(argv[2],O_RDWR);
        
                while((n = read(fd, buf1, 1)) > 0)
                {
                        write(STDOUT_FILENO, buf1, n);           
                        if(buf1[0] == '\n')
                        {
                                while((tobreak > 4) && ((j = read(fs, buf2, 1)) > 0))
                                {                        
                                        if (buf2[0] == '\n')
                                        {
                                                tobreak = 1;
                                        }                                             
                                        write(STDOUT_FILENO, buf2,j);                
                                }                                                     
                        }                                                             
                        tobreak = 5;
                }                                                                             
                while((j = read(fs, buf2, BLKSIZE)) > 0)
                        write(STDOUT_FILENO, buf2, j);
        }
}
