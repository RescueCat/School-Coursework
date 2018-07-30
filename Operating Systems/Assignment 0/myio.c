#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<ctype.h>
#include "myio.h"

inline int ReadInteger(void)
{
	char *str = ReadLine();
	int length = getLength(str), i = 0, flag = 1;


	for(; i < length; i++)
	{
		if(str[i] >= '9' || str[i] <= '0')
		{
			flag = 0;
		}
	}

	if(flag)
	{
		return atoi(str);
	}
	else
	{
		printf("Please try again(only integer)...\n");
		int x = ReadInteger();
		return x;
	}

}

double ReadDouble(void)
{
	char *str = ReadLine();
	int length = getLength(str), i = 0, flag = 1;

	for(; i < length; i++)
	{
			if((str[i] >= '9' || str[i] <= '0') && str[i] != '.')
			{
				flag = 0;
			}
	}

	if(flag && length < 17)
	{
			return strtod(str, NULL);
	}
	else
	{
			printf("Please try again (only double)...\n");
			double x = ReadDouble();
			return x;
	}
}

char * ReadLine(void) 
{
	char * line = malloc(100), * linep = line;
	size_t lenmax = 100, len = lenmax;
	int c;

	if(line == NULL)
		return NULL;

	for(;;) 
	{
		c = fgetc(stdin);
		if(c == EOF)
			break;

		if(--len == 0) 
		{
			len = lenmax;
			char * linen = realloc(linep, lenmax *= 2);

			if(linen == NULL) 
			{
				free(linep);
				return NULL;
			}
			line = linen + (line - linep);
			linep = linen;
		}

		if((*line++ = c) == '\n')
		{
			break;
		}
	}
	*line = '\0';
	return linep;
}

int getLength(char *line)
{
	int c, i = 0;
	char *temp = line;
	for(;;) 
	{
		c = *temp;
		if(c == EOF)
			break;

		if((*temp++ = c) == '\n')
		{
			break;
		}
		i++;
	}
	return i;
}

char *ReadLineFile(FILE *file)
{
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
	
	//return the line
	return buffer;
}
