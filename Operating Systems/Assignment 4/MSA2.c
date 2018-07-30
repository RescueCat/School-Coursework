#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUMBER_OF_THREADS 3

void *sorter(void *params);    
void *merger(void *params);  
double *list[]; 
double *result[];
int SIZE;

typedef struct
{
    	int from_index;
    	int to_index;
} parameters;

int main (int argc, const char * argv[])
{
	/* get size of array*/
	SIZE = atoi(argv[1]);
	*list  = (double *)malloc(SIZE * sizeof (double));
	*result = (double *)malloc(SIZE * sizeof(double));
	int j;
	double *random_value;
	srand(time(NULL));

	for(j=0; j < SIZE; j++)
	{
		random_value = (double*)rand();
		printf("%f \n", random_value);
		list[j] = random_value;
	}
	

    	int i;
    	pthread_t workers[NUMBER_OF_THREADS];

    	/* establish the first sorting thread */
    	parameters *data = (parameters *) malloc (sizeof(parameters));
    	data->from_index = 0;
    	data->to_index = (SIZE/2) - 1;
    	pthread_create(&workers[0], 0, sorter, data);

    	/* establish the second sorting thread */
    	data = (parameters *) malloc (sizeof(parameters));
    	data->from_index = (SIZE/2);
    	data->to_index = SIZE - 1;
    	pthread_create(&workers[1], 0, sorter, data);

    	/* now wait for the 2 sorting threads to finish */
    	for (i = 0; i < NUMBER_OF_THREADS - 1; i++)
        	pthread_join(workers[i], NULL);

    	/* establish the merge thread */
    	data = (parameters *) malloc(sizeof(parameters));
    	data->from_index = 0;
    	data->to_index = (SIZE/2);
   	pthread_create(&workers[2], 0, merger, data);

    	/* wait for the merge thread to finish */
    	pthread_join(workers[2], NULL);

    	/* output the sorted array */
    	return 0;
}

void *sorter(void *params)
{
    	parameters* p = (parameters *)params;

    	//SORT
    	int begin = p->from_index;
    	int end = p->to_index+1;
    	int z;

    	for(z = begin; z < end; z++)
    	{
        	printf("The array recieved is: %d\n", list[z]);
    	}
    	printf("\n");

    	int i,j,t,k;
    	for(i=begin; i< end; i++)
    	{
        	for(j=begin; j< end-i-1; j++)
        	{
            		if(list[j] > list[j+1])
            		{
                		t = list[j];
                		list[j] = list[j+1];
                		list[j+1] = t;
            		}
        	}
    	}

    	for(k = begin; k< end; k++)
	{
        	printf("The sorted array: %d\n", list[k]);
    	}

    	int x;
    	for(x=begin; x<end; x++)
    	{
            	result[x]=list[x];

    	}
    	printf("\n");

    	pthread_exit(0);

}

void *merger(void *params)
{
    	parameters* p = (parameters *)params;
   	
	//MERGE
    	int begin = p->from_index;
    	int end = p->to_index+1;
    	int i,j,t;

    	for(i=begin; i< end; i++)
    	{
        	for(j=begin; j< end-i; j++)
		{
            		if(result[j] > result[j+1])
            		{
                		t = result[j];
                		result[j] = result[j+1];
                		result[j+1] = t;
            		}
        	}
    	}

    	int d;
    	for(d=0; d<SIZE; d++)
    	{
        	printf("The final resulting array is: %d\n", result[d]);
    	}
    	pthread_exit(0);
}
