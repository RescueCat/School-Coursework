#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#define BLKSIZE 1024

void main (int argc, char *argv[])
{
        int n, i, j;
        int flagz = 0;
        char buf[BLKSIZE];
        int bytesread, byteswritten;

        for(j = 1; j < argc; j++)
        {
                if(strstr(argv[j],".out") != NULL)
                {
                        printf("%s is an .out file.\n",argv[j]);
                        flagz = 1;
                }
        }
        printf("%d\n", flagz);

        for(i = 1; i < argc; i++)
        {
                if(strstr(argv[i],".in") != NULL)
                {
                        int fd = open (argv[i],O_RDONLY);
                        if (fd < 0)
                                perror("incorrect usage");
                        else
                        {
                                        if(flagz = 1)
                                        {

                                                int gwrit = open(argv[argc-1], O_WRONLY | O_APPEND | O_CREAT, 0644);
                                                while((bytesread = read(fd,buf,BLKSIZE)) > 0)
                                                {
                                                        write(gwrit, buf, bytesread);
                                                }
                                        }
					else
                                        {
                                                printf("No file.out");
                                                while((bytesread = read(fd,buf,BLKSIZE)) > 0)
                                                        write(STDOUT_FILENO,buf,bytesread);
                                        }

			}	
		}	
	}
}
