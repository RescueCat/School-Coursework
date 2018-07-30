#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void main()
{
	//Variables
	int i, j, n = 4;
	
	//Create Pipes
	int pipes[4][2];
        for(i = 0; i < 4; i++)
	{
 		if((pipe(pipes[i])) < 0)
                {
                        perror("pipes");
                        exit(1);
                }
	}

	//Process ID
	pid_t pid[4];

	for(i = 1; i < n; i++)
	{
		if((pid[i] = fork()) < 0)
		{
			perror("fork");
			exit(1);
		}
		else if((pid[i] == 0))
		{
			//recursion removal here
			//do work on children
			//close all read ends except it's own
			for(j = 0; j < 4; j++)
			{
				if(j != i)
				{
					printf("Closing pipes[%d][0] for process %d\n", j, i);
					if(close(pipes[j][0]) < 0)
						perror("Failed to close read end of pipe");
				}
				else
				{
					//works! close it's own write end
					if(close(pipes[i][1]) < 0)
						perror("Could not close it's own write end");
				}	
			}
			exit(1);
		}
		sleep(1);
	}
	if(pid !=0)
	{
		wait(NULL);
		for(i = 1; i < n; i++)
		{
			printf("Closing pipes[%d][0] for Parent Process.\n", i);
			if(close(pipes[i][0]) < 0)
				perror("Could not close.");
		}
		pid[0] = getppid();
	}
	for(i = 0; i < 4; i++)
		printf("%d, ", pid[i]);
}
