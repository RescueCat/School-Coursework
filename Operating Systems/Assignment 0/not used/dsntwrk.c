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

	

	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
 
	stream = fopen("input_file.txt", "r");
	if (stream == NULL)
		exit(EXIT_FAILURE);
 
	while ((read = getline(&line, &len, stream)) != -1) 
	{
		printf("Retrieved line of length %zu :\n", read);
		printf("%s", line);
	}
 
	free(line);
	fclose(stream);
	exit(EXIT_SUCCESS);
}
