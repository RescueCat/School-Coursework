#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc, char *argv[]) 
{
	int addrtrans[] = {2, 4, 1, 7, 3, 5, 6};
   	int fdin, fdout;
   	unsigned long offset, page, physaddr, virtaddr;
   
   	if (argc != 2) 
	{
      		printf("Usage: %s <SEQUENCE FILE>\n", argv[0]);
      		exit(1);
   	}
   
   	if ((fdin = open(argv[1], O_RDONLY)) == -1) 
	{
      		perror("Main failed to open sequence file");
      		exit(2);
   	}
   
   	if ((fdout = open("output-part1", O_WRONLY | O_CREAT, 0600)) == -1) 
	{
      		perror("Main failed to open output file");
      		close(fdin);
      		exit(2);
  	}
   
   	while (read(fdin, &virtaddr, sizeof(virtaddr)) > 0) 
	{
      		offset = virtaddr & 0x7F;
      		page = virtaddr >> 7;
      		page = addrtrans[page];
      		physaddr = page << 7;
     	 	physaddr += offset;
      
      		if (write(fdout, &physaddr, sizeof(physaddr)) == -1) 
		{
         		perror("Main failed to write to output file");
         		exit(3);
      		}
   	}
   
   	close(fdin);
   	close(fdout);
   
   	return 0;
}
