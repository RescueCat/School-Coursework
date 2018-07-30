#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define BUFSIZE 9
#define WRTS 11
#define PROCS 9

void main()
{
	int n, i, rec, counter, parent, num, j;
	int pipes[PROCS][2];
	int RandNum[11];
	int messagecount = 0;
	
	struct message
	{
		char buf[BUFSIZE];
		int dex;
	}message;

	//Create Pipes
	for(i = 0; i < PROCS; i++)
	{
		if(pipe(pipes[i]) < 0)
			perror("Couldn't create pipe!\n");
	}

	//Fork & Switch
	for(i = 0; i < PROCS; i++)
	{
		switch(parent = fork())
		{
			case -1:
				perror("Could not fork!\n");
			case 0:
				counter = i;
				parent = 0;
				break;
			default:
				parent = 1;
				break;
		}
		if(parent == 0)
			break;
	}

	//Close Parent
	if(parent == 1)
		exit(0);

	//For Each Child

	//Close All Read Ends Except It's Own
	for(i = 0; i < PROCS; i++)
	{
		if(counter != i)
		{
			close(pipes[i][0]);
		}
	}
	
	//Generate Random Numbers
	srand(71917133 * counter); // seed
        for(n = 0; n < 11; n++)
        {
                do
                {
                        num = rand();
                        j = num % 9;
		}
		while(counter == j);
		RandNum[n] = j;
	}
                
	//Write a Message 	
	for(i = 0; i < WRTS; i++)
	{
		rec = RandNum[i];
		strcpy(message.buf, "process");
		message.dex = counter;
		write(pipes[rec][1], &message, sizeof(message));
		messagecount++;
	}

	//Close Write Ends of Pipe
	for(i = 0; i < PROCS; i++)
		close(pipes[i][1]);

	//Read All Messages & Store to Struct
	while(read(pipes[counter][0], &message, sizeof(message)) == sizeof(message))
	{
		printf("process%d has received a message from %s%d\n", counter, message.buf, message.dex);
		fflush(stdout);
	}

	//Close Child
	close(pipes[counter][0]);
	exit(0);
}
