#include <stdio.h>
#include "pslibrary.h"

void main(int argc, char *argv[])
{
    	int arraySize = 0;

    	if(!(argc == 8))	
	{
        	printf("Not enough arguments, there must be atleast 8.\n");
        	return;
     	}

    	printf("Assignment 1 program written by Jonathan Houston\n");

    	printf("inputs: ");

    	int i = 1;
    	for(; i < argc; i++)
	{
        	printf("%c ", *argv[i]);
        	if(i > 1)
		{
            		arraySize += *argv[i] - 48;
        	}
    	}
    
	int value[arraySize];
    
	for(i = 2; i < argc; i++)
	{
        	value[i-2] = *argv[i] - 48;
    	}

    	char str1[arraySize];
    	char str2[arraySize];

    	fcfsa(str1, str2, value[0], value[1], value[2], value[3], value[4], value[5]);
    	display("Part0\n", str1, str2);
}
