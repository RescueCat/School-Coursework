#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main (int argc, const char * argv[])
{

        /* get size of array*/
        int SIZE = atoi(argv[1]);
        double *list  = (double *)malloc(SIZE * sizeof (double));
	list[SIZE];
        int j;
        double random_value;
        srand(time(NULL));
        //result[SIZE];

        for(j=0; j < SIZE; j++)
        {
                random_value = (double)rand();
                printf("%f \n", random_value);
                list[j] = random_value;
        }
}
