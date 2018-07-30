#include <stdio.h>
#include <stdlib.h>

void main (int argc, char *argv[])
{
	//gets three command-line arguments: x y z. no more no less.
	if (argc > 4)
	{
		perror("Too many arguments.\n");
		exit(0);
	}
	if (argc < 4)
	{
		perror("Not enough arguments.\n");
		exit(0);
	}

	int x = atoi(argv[1]);
	int y = atoi(argv[2]);
	int z = atoi(argv[3]);

	//arrays to hold our values
	int xnum[x], xbig = 0, xcomp;
	float ynum[y], ybig = 0, ycomp;
	char *znum[z];
	int zbig = 0, zcomp;
	

	//printf("%d %d %d \n", x, y, z);
	//It then asks user to enter x many integers
	int i;
	for(i = 0; i < x; i++)
	{
		printf("Please enter an integer for array x: ");
		xnum[i] = ReadInteger();			
		xcomp = xnum[i];

		if(xbig < xcomp)
		{
			xbig = xcomp;
		}		
	}
	
	//y many doubles
	int where2 = 0;
	for(i = 0; i < y; i++)
        {
                printf("Please enter a double for array y: ");
                ynum[i] = ReadDouble();
	        //scanf("%f", &ynum[i]);
		ycomp = ynum[i];

                if(ybig < ycomp)
                {
                        ybig = ycomp;
			where2 = i;
                }
        }

	//and z many lines
	int where = 0;
        for(i = 0; i < z; i++)
        {
                printf("Please enter a line of text for array z: ");
		znum[i] = ReadLine();
		zcomp = getLength(znum[i]);
		
		if(zbig < zcomp)
		{
			zbig = zcomp;
			where = i;	
		}
        }
	
	printf("The biggest integer was %d!\n", xbig);
	//printf("The biggest double was %f!\n", ynum[where2]);
	printf("The biggest line was %s\n", znum[where]);
}

