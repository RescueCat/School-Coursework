#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

char *process(char*);

int main(int argc, char* argv[])
{
    	char const* const fileName = argv[1]; /* should check that argc > 1 */
    	FILE* file = fopen(fileName, "r"); /* should check the result */
    	
	char *s;
	s = ReadLineFile(file);
	/*
	char *buffer;
	long lSize;
	
	//find the size of the file
    	fseek(file, 0L, SEEK_END);
	lSize = ftell(file);
	rewind(file);

	//make memory for the file
	buffer = calloc(1, lSize+1);

	//copy file into buffer
	fread(buffer, lSize, 1, file);
	*/

	//Edit buffer for no double spaces
	//char *s = buffer;
	char *text;

	text = process(s);	
	
	//write to file
	char const* const fileName2 = argv[2];
	FILE* file2 = fopen(fileName2, "w+");
	fputs(text, file2);	
	//fwrite(text, 1, sizeof(text), file2);

	//free memory
	fclose(file);
	//free(buffer);
    	return 0;
}

char *process(char *text) 
{
   	int length, c, d;
   	char *start;
 
   	c = d = 0;
 
   	length = strlen(text);
 
   	start = (char*)malloc(length+1);
 
   	if (start == NULL)
      		exit(EXIT_FAILURE);
 
   	while (*(text+c) != '\0') 
	{
      		if (*(text+c) == ' ') 
		{
         		int temp = c + 1;
         		if (*(text+temp) != '\0') 
			{
            			while (*(text+temp) == ' ' && *(text+temp) != '\0') 
				{
               				if (*(text+temp) == ' ') 
					{
                  				c++;
               				}  
               				temp++;
            			}
         		}
      		}
      		*(start+d) = *(text+c);
      		c++;
      		d++;
   	}
   	
	*(start+d)= '\0';
   	return start;
}
