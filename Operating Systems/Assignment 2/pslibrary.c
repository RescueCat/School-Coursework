#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

#define READY  0
#define RUNNING  1
#define WAITING  2
#define DONE  3

static char stateChars[] = {'r','R','w',0};

/* 1) handle state changes:
         running process completes CPU burst
         running process has quantum expire
         IO complete
   2) do context switch if necessary
         both ready
         one ready and CPU free
   3) append appropriate characters to character arrays
         avoid putting in multiple string terminators
*/
/* assume s1 and s2 point to buffers with enough space to hold the result */
/* assume that the int parameters are strictly greater than 0 */
void fcfs(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) 
{
    	int i;                                   /* next string position (time) */
    	int state1 = READY;                            /* start with both ready */
    	int state2 = READY;
    	int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
    	int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
    	int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
    	int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */
    	int qleft;                                         /* quantum remaining */

    	for (i=0; (state1 != DONE) || (state2 != DONE); i++) 
	{
        	/* running process completes its CPU burst */
        	if ((state1 == RUNNING) && (cpuLeft1== 0)) 
		{
            		if (ioLeft1 == 0) 
			{
                		state1 = DONE;
                		s1[i] = stateChars[state1];            /* terminate the string */
            		}
            		else
                		state1 = WAITING;
        	}
        	else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) 
		{
            		if (ioLeft2 ==0)
			{
                		state2 = DONE;
                		s2[i] = stateChars[state2];
            		}
            		else
                		state2 = WAITING;
        	}
        		
		/* handle IO complete */
        	if ((state1 == WAITING) && (ioLeft1 == 0)) 
		{
            		state1 = READY;
         		cpuLeft1 = z1;
        	}
        	if ((state2 == WAITING) && (ioLeft2 == 0)) 
		{
            		state2 = READY;
            		cpuLeft2 = z2;
        	}
        		
		/* if both ready, depends on algorithm */
        	if ( (state1 == READY) && (state2 == READY)) 
		{
            		state1 = RUNNING;
            		state2 = READY;
        	}
        		
		/* handle one ready and CPU available */
        	else if ( (state1 == READY) && (state2 != RUNNING)) 
		{
            		state1 = RUNNING;
        	}
        	else if ( (state2 == READY) && (state1 != RUNNING)) 
		{
            		state2 = RUNNING;
        	}
        
		/* insert chars in string, but avoid putting in extra string terminators */
        	if (state1 != DONE)
            		s1[i] = stateChars[state1];
        	if (state2 != DONE)
            		s2[i] = stateChars[state2];
       
		/* decrement counts */
        	qleft--;                   /* OK to decrement even if nothing running */
        	if (state1 == RUNNING)
            		cpuLeft1--;
        	if (state1 == WAITING)
            		ioLeft1--;
        	if (state2 == RUNNING)
            		cpuLeft2--;
        	if (state2 == WAITING)
            		ioLeft2--;
    	}                                               /* end of main for loop */
}

/* 1) handle state changes:
         running process completes CPU burst
         running process has quantum expire
         IO complete
   2) do context switch if necessary
         both ready
         one ready and CPU free
   3) append appropriate characters to character arrays
         avoid putting in multiple string terminators
*/
/* assume s1 and s2 point to buffers with enough space to hold the result */
/* assume that the int parameters are strictly greater than 0 */
void sjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) 
{
    	int i;                                   /* next string position (time) */
    	int state1 = READY;                            /* start with both ready */
    	int state2 = READY;
    	int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
    	int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
    	int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
    	int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */

    	if(x1 > x2)
	{
        	char *temp = s2;
        	s2 = s1;
        	s1 = temp;
        	cpuLeft1 = x2;
        	cpuLeft2 = x1;
        	ioLeft1 = y2;
        	ioLeft2 = y1;
    	}
    	
	for (i=0; (state1 != DONE) || (state2 != DONE); i++) 
	{
        	/* running process completes its CPU burst */
        	if ((state1 == RUNNING) && (cpuLeft1== 0)) 
		{
            		if (ioLeft1 == 0) 
			{
                		state1 = DONE;
                		s1[i] = stateChars[state1];            /* terminate the string */
            		}
            	else
                	state1 = WAITING;
        	}
        	else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) 
		{
            		if (ioLeft2 ==0)
			{
                		state2 = DONE;
                		s2[i] = stateChars[state2];
            		}
            		else
                	state2 = WAITING;
        	}
        
		/* handle IO complete */
        	if ((state1 == WAITING) && (ioLeft1 == 0)) 
		{
            		state1 = READY;
            		cpuLeft1 = z2;
        	}
        	if ((state2 == WAITING) && (ioLeft2 == 0)) 
		{
            		state2 = READY;
            		cpuLeft2 = z1;
        	}
        
		/* if both ready, depends on algorithm */
        	if ( (state1 == READY) && (state2 == READY)) 
		{
            		state1 = RUNNING;
            		state2 = READY;
        	}
        
		/* handle one ready and CPU available */
        	else if ( (state1 == READY) && (state2 != RUNNING)) 
		{
            		state1 = RUNNING;
        	}
        	else if ( (state2 == READY) && (state1 != RUNNING)) 
		{
            		state2 = RUNNING;
        	}
        
		/* insert chars in string, but avoid putting in extra string terminators */
        	if (state1 != DONE)
            		s1[i] = stateChars[state1];
        	if (state2 != DONE)
            		s2[i] = stateChars[state2];
        
		/* decrement counts */
        	if (state1 == RUNNING)
            		cpuLeft1--;
        	if (state1 == WAITING)
            		ioLeft1--;
        	if (state2 == RUNNING)
            		cpuLeft2--;
        	if (state2 == WAITING)
            		ioLeft2--;
    	}                                               /* end of main for loop */
}

void psjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) 
{
	int i;                                   /* next string position (time) */
    	int state1 = READY;                            /* start with both ready */
    	int state2 = READY;
    	int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
    	int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
    	int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
    	int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */
    	int swapped = 0;

    	if(x1 > x2)
	{
        	char *temp = s2;
        	s2 = s1;
        	s1 = temp;
        	cpuLeft1 = x2;
        	cpuLeft2 = x1;
        	ioLeft1 = y2;
        	ioLeft2 = y1;
        	swapped = 1;
    	}
    	
	/*start main loop*/
	for (i=0; (state1 != DONE) || (state2 != DONE); i++) 
	{
        	/* running process completes its CPU burst */
        	if ((state1 == RUNNING) && (cpuLeft1== 0)) 
		{
            		if (ioLeft1 == 0) 
			{
                		state1 = DONE;
                		s1[i] = stateChars[state1];            /* terminate the string */
            		}
            		else
                		state1 = WAITING;
        	}
        	else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) 
		{
            		if (ioLeft2 ==0)
			{
                		state2 = DONE;
                		s2[i] = stateChars[state2];
            		}
            		else
                		state2 = WAITING;
        	}
        
		/* handle IO complete */
        	if ((state1 == WAITING) && (ioLeft1 == 0)) 
		{
            		state1 = READY;
            		if(swapped)
			{
				cpuLeft1 = z2;
			}
            		else
			{
				cpuLeft1 = z1;
			}
        	}
        	if ((state2 == WAITING) && (ioLeft2 == 0)) 
		{
            		state2 = READY;
            		if(swapped)
			{
				cpuLeft2 = z1;
			}
           		else
			{
				cpuLeft2 = z2;
			}
        	}
        
		/* if both ready, depends on algorithm */
        	if ( (state1 == READY) && (state2 == READY)) 
		{
            			state1 = RUNNING;
            			state2 = READY;
        	}
        
		/* handle one ready and CPU available */
        	else if ( (state1 == READY) && (state2 != RUNNING)) 
		{
            		state1 = RUNNING;
        	}
        	else if ( (state2 == READY) && (state1 != RUNNING)) 
		{
            		state2 = RUNNING;
        	}
        
		/* insert chars in string, but avoid putting in extra string terminators */
        	if (state1 != DONE)
            		s1[i] = stateChars[state1];
        	if (state2 != DONE)
            		s2[i] = stateChars[state2];
        
		/* decrement counts */
        	if (state1 == RUNNING)
            		cpuLeft1--;
        	if (state1 == WAITING)
            		ioLeft1--;
        	if (state2 == RUNNING)
            		cpuLeft2--;
        	if (state2 == WAITING)
           		 ioLeft2--;

        	if(state1 == READY && state2 == RUNNING)
		{
            		if(cpuLeft1 < cpuLeft2)
			{
                		state1 = RUNNING;
                		state2 = READY;
            		}
        	}
  	}                                               /* end of main for loop */
}

void rr(char *s1, char *s2, int q, int x1, int y1, int z1, int x2, int y2, int z2)
{
    	int i;                                   /* next string position (time) */
    	int state1 = READY;                            /* start with both ready */
    	int state2 = READY;
    	int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
    	int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
    	int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
    	int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */
    	int swapped = 0;
    	int k = 0;

    	for (i=0; (state1 != DONE) || (state2 != DONE); i++,k++) 
	{
        	if ( k == q && swapped == 0)
		{
                	swapped = 1;
        	}
        	else if(k == q && swapped == 1)
		{
                	swapped = 0;
        	}

       	 	if(state1 == DONE)
		{
            		swapped = 1;
            		if(k >= q)
			{
                		k = 0;
            		}
        	}
        	if(state2 == DONE)
		{
            		swapped = 0;
            		if(k >= q)
			{
                		k = 0;
            		}
        	}

        	/* running process completes its CPU burst */
        	if ((state1 == RUNNING) && (cpuLeft1== 0)) 
		{
            		if (ioLeft1 == 0) 
			{
                		state1 = DONE;
                		s1[i] = stateChars[state1];            /* terminate the string */
            		}
            		else
               			 state1 = WAITING;
        	}
        	else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) 
		{
            		if (ioLeft2 ==0)
			{
                		state2 = DONE;
                		s2[i] = stateChars[state2];
            		}
            		else
                		state2 = WAITING;
        	}
        
		/* handle IO complete */
        	if ((state1 == WAITING) && (ioLeft1 == 0)) 
		{
            		state1 = READY;
            		cpuLeft1 = z1;
            		if(state2 == DONE || state2 == WAITING)
				state1 = RUNNING;
        	}
        	if ((state2 == WAITING) && (ioLeft2 == 0)) 
		{
            		state2 = READY;
            		cpuLeft2 = z2;
            		if(state1 == DONE || state1 == WAITING)
			{
                		state2 = RUNNING;
            		}
        	}
        
		/* if both ready, depends on algorithm */
        	if ( (state1 == READY) && (state2 == READY))
		{
            		if(k <= q)
			{
                		if(swapped)
				{
                    			state2 = RUNNING;
                    			if (k == q)
					{
                        			k = 0;
                    			}
                		}
                		else
				{
                    			state1 = RUNNING;
                    			if (k == q)
					{
                        			k = 0;
                    			}
                		}
            		}
            		else if(k == 0)
			{
                		state1 = RUNNING;
            		}
        	} 
		
		/* handle one ready and CPU available */
        	else if ( (state1 == READY ) && state2 != RUNNING && k == q && swapped == 0) 
		{
            		state1 = RUNNING;
            		k = 0;
        	}
        	else if ( (state2 == READY) && (state1 != RUNNING && k == q && swapped == 1) ) 
		{
                	state2 = RUNNING;
                	k = 0;
        	}
       	 	else if(state1 == RUNNING && state2 == READY && k == q)
		{
            		state1 = READY;
            		state2 = RUNNING;
            		k = 0;
        	}
        	else if(state1 == READY && state2 == RUNNING && k == q)
		{
            		state1 = RUNNING;
            		state2 = READY;
            		k = 0;
        	}
        	else if(state1 == READY && (state2 == DONE || state2 == WAITING))
		{
            		state1 = RUNNING;
        	}
        	else if(state2 == READY && (state1 == DONE || state1 == WAITING))
		{
            		state2 = RUNNING;
        	}

        	if(k == 3 && state1 == WAITING && state2 == WAITING)
		{
            		k = 0;
        	}
        
		/* insert chars in string, but avoid putting in extra string terminators */
        	if (state1 != DONE)
            		s1[i] = stateChars[state1];
        	if (state2 != DONE)
            		s2[i] = stateChars[state2];
        
		/* decrement counts */
        	if (state1 == RUNNING)
            		cpuLeft1--;
        	if (state1 == WAITING)
            		ioLeft1--;
        	if (state2 == RUNNING)
            		cpuLeft2--;
        	if (state2 == WAITING)
            		ioLeft2--;
    	}
}


void display(char *heading, char *s1, char *s2)
{
	int length2 = 0;
    	int length1 = 0;
    	double r1 = 0.0, r2 = 0.0;
    	double bigR = 0.0, larger = 0.0;
    	int i = 0, k = 0, h = 0, g = 0;

    	for(; h < strlen(s1) + 1; h++)
	{
        	if(s1[h] == 'R' || s1[h] == 'r' ||s1[h] == 'w')
		{
            		length1++;
        	}
    	}

    	for(; g < strlen(s2) + 1; g++)
	{
       		if(s2[g] == 'R' || s2[g] == 'r' ||s2[g] == 'w')
		{
            		length2++;
        	}
    	}	

    	for(; i < length1; i++)
	{
        	if(s1[i] == 'r')
		{
            		r1++;
        	}
        	if(s1[i] == 'R')
		{
            		bigR++;
        	}
    	}

    	for(; k < length2; k++)
	{
        	if(s2[k] == 'r')
		{
            		r2++;
        	}
        	if(s2[k] == 'R')
		{
            		bigR++;
        	}
    	}

    	if(length2 > length1)
	{
        	larger = length2;
    	}
    	else
	{
        	larger = length1;
    	}

    	char path[100] = "REPORT.txt";
    	FILE *fp;
    	fp = fopen(path, "a+");
    	if(!fp)
	{
        	printf( "Error code opening file: %d\n", errno );
        	printf( "Error opening file: %s\n", strerror( errno ) );
        	exit (1);
    	}

    	double rAvg = (r1 + r2)/2;
    	double cpuUsage = bigR/larger;
    	s1[length1] = 0;
    	s2[length2] = 0;

    	printf("\n\n");
    	fprintf(fp, "\n\n");
    	printf("%s", heading);
    	fprintf(fp, "%s", heading);

    	printf("%s\n", s1);
    	fprintf(fp, "%s\n", s1);
    	printf("%s\n", s2);
    	fprintf(fp, "%s\n", s2);
    	printf("%.0f %.0f %.1f %.5f", r1, r2, rAvg, cpuUsage);
    	fprintf(fp, "%.0f %.0f %.1f %.5f", r1, r2, rAvg, cpuUsage);
    	printf("\n");
    	fprintf(fp, "\n");

    	fclose(fp);
}

void fcfsa_assign1(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2)
{
    	int i = 0, k = 0;

    	for(; i < x1; i++)
	{
        	s1[i] = 'R';
        	s2[i] = 'r';
    	}

    	k = i;

    	int l = i;
    	for(;l < y1+i; l++)
	{
        	s1[l] = 'w';
    	}
    	i += y1;

    	int m = k;
    	for(;m < x2+k; m++)
	{
        	s2[m] = 'R';
    	}
    	k += x2;

    	int n = k;
    	for(;n < y2+k; n++)
	{
        	s2[n] = 'w';
    	}
    	k += y2;


    	if(x2 > y1)
	{
        	for(l = i; l < (x2-y1)+i; l++)
		{
            		s1[l] = 'r';
        	}
		i += (x2-y1);
        	for(n = i; n < z1+i; n++)
		{
            		s1[n] = 'R';
        	}
        	i += z1;

        	if (y2 < z1)
		{
            		for(n = k; n < (z1 - y2)+k; n++)
			{
                		s2[n] = 'r';
            		}
            		k += (z1-y2);
            		for(l = k; l < z2+k; l++)
			{
                		s2[l] = 'R';
            		}
            		k += z2;
        	}
        	else
		{
            		for(l = k; l < z2+k; l++)
			{
                		s2[l] = 'R';
            		}
            		k += z2;
        	}
    	}
    	else if(x2 < y1)
	{
        	if( (x2 + y2) < y1)
		{
            		for(l = k; l < (y1 - (x2+y2)) + k; l++)
			{
                		s2[l] = 'R';
            		}
            		k += (y1 - (x2+y2));
            		for(m = i; m < (x2+y2+z2-y1) + i; m++)
			{
                		s1[m] = 'r';
            		}
            		i += (x2+y2+z2-y1);
            		for(n = i; n < z1 + i; n++)
			{
                		s1[n] = 'R';
            		}
            		i += z1;
        	}
        	else if( (x2 + y2) == y1)
		{
            		for(l = i; l < z1+i; l++)
			{
                		s1[l] = 'R';
            		}
            		i += z1;
            		for(m = k; m < z1+k; m++)
			{
                		s2[m] = 'r';
            		}
           		k += z1;
            		for(n = k; n < z2+k; n++)
			{
                		s2[n] = 'R';
            		}
            		k += z2;
        	}
        	else
		{
            		for(l = i; l < z1+i; l++)
			{
                		s1[l] = 'R';
            		}
            		i += z1;
            		if ( (x2 + y2) < (y1 + z1) )
			{
                		for(m = k; m < (z1+y1)-(x2+y2)+k; m++)
				{
                    			s2[m] = 'r';
                		}
                		k += (z1+y1)-(x2+y2);
                		for(n = k; n < z2+k; n++)
				{
                    			s2[n] = 'R';
                		}
                		k += z2;
            		}
            		else
			{
                		for(n = k; n < z2+k; n++)
				{
                    			s2[n] = 'R';
                		}
                		k += z2;
            		}	
        	}
	}
	else
	{
		for(l = i; l < z1+i; l++)
		{
        		s1[l] = 'R';
		}
        	i += z1;
        	for(m = k; m < y2+k; m++)
		{
            		s2[m] = 'w';
        	}
        	k += y2;

        	if(y2 < z1)
		{
            		for(l = k; l < y2+k; l++)
			{
                		s2[l] = 'r';
            		}
            		k += y2;
            		for(m = k; m < z2+k; m++)
			{
                		s2[m] = 'R';
            		}
            		k += z2;
        	}
        	else
		{
            		for(l = k; l < z2+k; l++)
			{
                		s2[l] = 'R';
            		}
            		k += z2;
        	}
    	}
}
