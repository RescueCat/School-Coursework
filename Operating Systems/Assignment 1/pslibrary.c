#include<stdio.h>
#include<string.h>

void part0(char *s1, char *s2)
{
    	char *string1 = "RRwwwwwRRRRRRRRR";
    	char *string2 = "rrRRRRwwwwwwwwrrRRRRRRR";
    	int i = 0, k = 0;

    	int length2 = strlen(string2) + 1;
    	int length1 = strlen(string1) + 1;

    	for(; i < length1; i++)
	{
        	s1[i] = string1[i];
    	}

    	for(; k < length2; k++)
	{
        	s2[k] = string2[k];
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

    	double rAvg = (r1 + r2)/2;
    	double cpuUsage = bigR/larger;
    	s1[length1] = NULL;
    	s2[length2] = NULL;

    	printf("\n\n");
    	printf("%s", heading);
    	printf("%s\n", s1);
    	printf("%s\n", s2);
    	printf("%.0f %.0f %.1f %.5f", r1, r2, rAvg, cpuUsage);
    	printf("\n");
}

void fcfsa(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2)
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

        	if(y2 < z1)
		{
            		for(l = k; l < (y1+z1)-(x2+y2)+k; l++)
			{
                		s2[l] = 'r';
            		}
            		k += (y1+z1)-(x2+y2);
            
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
