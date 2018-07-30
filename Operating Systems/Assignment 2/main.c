nclude <stdio.h>
#include "pslibrary.h"
#include<errno.h>
#include<stdlib.h>
#include<string.h>

/*
 * int main(int argc, char *argv[])
{
    	int arraySize = 0;
    	if(!(argc == 8))
	{
        	printf("Not enough arguements or too many arguments.");
        	return -1;
    	}
    
	int i = 1;
    	for(; i < argc; i++)
	{
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
    	
	char path[100] = "REPORT.txt";
    	FILE *fp;
    	fp = fopen(path, "a+");
    	if(!fp)
	{
        	printf( "Could not open file: %d\n", errno );
        	printf( "Error opening file: %s\n", strerror( errno ) );
        	exit (1);
    	}
    
	printf("Assignment 1 program written by Jonathan Houston\n");
    	fprintf(fp, "\nAssignment 1 program written by Jonathan Houston\n");
    	printf("Inputs: %d %d %d %d %d %d %d\n", *argv[1]-48, value[0], value[1], value[2], value[3], value[4], value[5]);
    	fprintf(fp, "Values: %d %d %d %d %d %d %d\n", *argv[1]-48, value[0], value[1], value[2], value[3], value[4], value[5]);
    	fclose(fp);
    
	char str1Proto[arraySize];
   	char str2Proto[arraySize];
    	char str1SFJ[arraySize];
    	char str2SJF[arraySize];
    	char str1PSJF[arraySize];
    	char str2PSJF[arraySize];
    	char str1RR[arraySize];
    	char str2RR[arraySize];
    
	proto(str1Proto, str2Proto, value[0], value[1], value[2], value[3], value[4], value[5]);
    	display("FCFS\n", str1Proto, str2Proto);
    	sjf(str1SFJ, str2SJF, value[0], value[1], value[2], value[3], value[4], value[5]);
    	display("SJF\n", str1SFJ, str2SJF);
    	psjf(str1PSJF, str2PSJF, value[0], value[1], value[2], value[3], value[4], value[5]);
    	display("PSJF\n", str1PSJF, str2PSJF);
    	rr(str1RR, str2RR, *argv[1]-48, value[0], value[1], value[2], value[3], value[4], value[5]);
    	display("RR\n", str1RR, str2RR);
    	return 0;
}
*/
