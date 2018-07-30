#include <stdlib.h>
#include "pagetable.h"

int** initializeTable(int*** table, int size) 
{
      	*table = (int **)malloc(size * sizeof(int*));
      
      	int x;
      	for (x = 0; x < size; x++) 
	{
         	(*table)[x] = (int *)malloc(2 * sizeof(int));
         	(*table)[x][0] = NONE;
         	(*table)[x][1] = i;
      	}
      
      	return *table;
}

int** pointPage(int*** table, int virtpage, int physframe) 
{
      	(*table)[virtpage][0] = physframe;
      	(*table)[virtpage][1] = v;
      
      	return *table;
}

void freeTable(int*** table, int size) 
{
   	int x;
   	for (x = 0; x < size; x++)
      		free((*table)[x]);
   
   	free(*table);
}
