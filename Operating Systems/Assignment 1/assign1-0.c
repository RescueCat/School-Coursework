#include <stdio.h>
#include "pslibrary.h"

void main(int argc, char *argv[])
{
    	int arraySize = 0;

    	if(!(argc == 8))	
	{
        	printf("Not enough arguements, there must be atleast 8.\n");
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
    
	printf("\n");
    	printf("arraySize: %d\n", arraySize);

    	char str1[arraySize];
    	char str2[arraySize];

    	part0(str1, str2);
    	display("Part0\n", str1, str2);

	int k = 0;
	int length2 = sizeof(str2)/sizeof(str2[0]);
	
	while(str2[k] != 0 || str2[k] != NULL)
	{
		printf("%c ", str2[k]);
		k++;
	}
}
