#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

//Define a very basic PCB structure
struct PCB
{
	int ProcId; int ProcPR; int CPUburst; int Reg[8];
        int queueEnterClock; int waitingTime; struct PCB *next;
};

//Define a very basic CPU consisting of 8 integer registers
int CPUreg[8] = {0};

//Initialize your linked list:
struct PCB *Head=NULL;
struct PCB *Tail=NULL;

//define my append function to create nodes
void AddNode(struct PCB** head_ref, int Pid, int PrP, int CpuB); 

//define my fifo scheduling function 
void FIFO_Scheduling(struct PCB *node, int CLOCK, double Total_waiting_time, double Total_turnaround_time, double Total_job)
{
	int i;
	while(node != NULL)
	{
        	for(i = 0; i < 8; i++)
        	{
			//copy PCB->Reg[8] into CPUreg[8],
			CPUreg[i] = node-> Reg[i];
			
			/*suppose some work is done on CPU 
			(e.g, increment each CPUreg by one),*/
         		CPUreg[i] += 1;

			//copy CPUreg[8] into PCB->Reg[8] 
			node-> Reg[i] = CPUreg[i];
		}

		//Data Collection for Performance metrics
	        node-> waitingTime = 
			node-> waitingTime + CLOCK - node-> queueEnterClock;
		Total_waiting_time = Total_waiting_time + node-> waitingTime;
		CLOCK = CLOCK + node-> CPUburst;	
		Total_turnaround_time = Total_turnaround_time + CLOCK;
		Total_job = Total_job + 1;
		
		//Print while running
		printf("Process %d is completed at %d ms \n", node-> ProcId, CLOCK);
		
		//go to next
		node = node-> next;
        }

	//print performance metrics	
	printf("\nAverage Waiting time = %G ms\n", Total_waiting_time / Total_job);
	printf("Average Turnaround time = %G ms\n", Total_turnaround_time / Total_job);
	printf("Throughput = %G jobs per ms\n", Total_job / CLOCK);
	
	//free PCB
	free(node);
	return;
}

/*printlist
// This function prints contents of linked list starting from head
void printList(struct PCB *node)
{
	while (node != NULL)
  	{
     		printf(" %d ", node-> Reg[0]);
     		node = node->next;
  	}
}*/

int main(int argc, char* argv[])
{	
	//Initialize your other data
	int CLOCK=0; 
	double Total_waiting_time = 0; 
	double Total_turnaround_time = 0; 
	double Total_job = 0;
	char const* const Alg = argv[2];	

	//Open the input file
	char const* const fileName = argv[4];
	FILE* file = fopen(fileName, "r");

	//For each input line,
	char line[256];//line can be optimized (smaller) but not necessary for assign
	int a, b, c;
	while(fgets(line, sizeof(line), file))
	{
		sscanf(line,"%d	%d %d", &a, &b, &c);
		AddNode(&Head, a, b, c);
	}

	//close file
	fclose(file);
	
	//Print your name, the name of scheduling algorithm, and the input file name
	printf("Student Name: Jonathan Houston\n");
	printf("Input File Name : %s\n", fileName);
	printf("CPU Scheduling Alg : %s\n\n", Alg);

	// implement a FIFO_Scheduling()function
	FIFO_Scheduling(Head, CLOCK, Total_waiting_time, Total_turnaround_time, Total_job);
	//printList(Head);
}

/* Given a reference (pointer to pointer) to the head
   of a list and some other data, adds a new node at the end  */
void AddNode(struct PCB** head_ref, int Pid, int PrP, int CpuB)
{
    /* 1. allocate node */
    	struct PCB* new_node = (struct PCB*) malloc(sizeof(struct PCB));
 
    	struct PCB *last = *head_ref;//can use tail here but not neccesary for assign
  
    /* 2. put in the data  */
    	new_node-> ProcId = Pid;
	new_node-> ProcPR = PrP;
	new_node-> CPUburst = CpuB; 
 
	//set all PCB->Reg[8] to the Process ID
	int i;
	for(i = 0; i < 8; i++)
	{
		new_node-> Reg[i] = Pid;
	}

	//set PCB->queueEnterClock and PCB->waitingTime to 0
	new_node-> queueEnterClock = 0;
	new_node-> waitingTime = 0;

    /* 3. This new node is going to be the last node, so make next 
          of it as NULL*/
    	new_node-> next = NULL;
 
    /* 4. If the Linked List is empty, then make the new node as head */
    	if (*head_ref == NULL)
    	{
       		*head_ref = new_node;
       		return;
    	}  
      
    /* 5. Else traverse till the last node */
    	while (last-> next != NULL)
        	last = last-> next;
  
    /* 6. Change the next of last node */
    	last-> next = new_node;
    	return;    
}
