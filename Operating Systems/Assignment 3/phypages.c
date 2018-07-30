#include <stdlib.h>
#include "phypages.h"

int* initializeFrames(int** frames, int size) 
{
      	*frames = (int *)malloc(size * sizeof(int));
      
      	(*frames)[0] = OS;
      
      	int x;
      	for (x = 1; x < size; x++) 
	{
         	(*frames)[x] = NONE;
      	}
      
      	return *frames;
}

int findOpen(int** frames, int size) 
{
      	int frame = -1;
      
      	int x;
      	for (x = 1; x < size; x++) 
	{
         	if ((*frames)[x] == -1) 
		{
            		frame = x;
            		break;
         	}	
      	}
      
      	return frame;
}

int* reverseMap(int** frames, int frame, int page) 
{
      	(*frames)[frame] = page;
      
      	return *frames;
}
