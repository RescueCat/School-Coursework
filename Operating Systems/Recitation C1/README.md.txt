CS 3733 Operating Systems, Recitation Session C1
In this session, you will set up your account to implement necessary linked list functions for FIFO CPU scheduling and perform the very basic steps in context-switching. In the next session, you will extend this program to implement other three basic CPU scheduling algorithms (namely, SJF, PR, and RR with a given quantum). To keep it simle, we assume each process has a single CPU burst without any I/O burst and that all processes arrive at the same time in a given order. The order of processes will be given in a simple input file. Each line in the input file consists of three integer numbers: Process Id, Process Priority, CPU Burst time (ms). Download input1.txt  as a sample input file. 
Your program will take the name of the scheduling algorithm, related parameters (if any), and an input file name from command line. In general, here how your program should be executed:

> prog -alg [FIFO|SJF|PR|RR] [-quantum [integer(ms)]] -input [input_file_name.txt]

In this session, you will just run it as:

> prog -alg FIFO -input input1.txt

For the given input file, the output of your program will be as follows:

Student Name: Your name
Input File Name : input1.txt 
CPU Scheduling Alg : FIFO 

Proces 1 is completed at 5 ms
Proces 2 is completed at 12 ms 
Proces 3 is completed at 18 ms 
Proces 4 is completed at 22 ms 

Average Waiting time =  8.75 ms     (35/4)
Average Turnaround time = 14.25 ms  (57/4)
Throughput = 0.18 jobs per ms       (4/22)  
In the next session, you will implement and test other three CPU scheduling algorithms.

Detailed steps for this session
Log on to your Linux Account.
Create a directory called RecC1 under cs3733 and do all your work under RecC1.
-----------------------------------------
Define a very basic PCB structure: struct PCB {int ProcId; int ProcPR, int CPUburst; int Reg[8]; int queueEnterClock, waitingTime; /* other info */ struct PCB *next;}
Define a very basic CPU consisting of 8 integer registers: int CPUreg[8] = {0};
Initialize your linked list: struct PCB *Head=NULL; struct PCB *Tail=NULL;
Initialize your other data: int CLOCK=0; int Total_waiting_time=0; int Total_turnaround_time=0; int Total_job=0;
Open the input file
For each input line,
read a line consisting of three integers: Process Id, Process Priority, CPU Burst time.
dynamically create a struct PCB pointed by PCB,
save the given data into correponding fields of PCB,
set all PCB->Reg[8] to the Process ID, set PCB->queueEnterClock and PCB->waitingTime to 0, then
insert this PCB at the end of the link list.
Close input file
Print your name, the name of scheduling algorithm, and the input file name, as mentioned before.
------------------ The above steps will be the same for the next session too -----------------------
Now implement a FIFO_Scheduling() function and call it to print the order of completed processes.
This function simply removes the PCB from the head of the linked list and performs the followings until the linked list is empty:  
Do context-switching:
copy PCB->Reg[8] into CPUreg[8],
suppose some work is done on CPU (e.g, increment each CPUreg by one),
copy CPUreg[8] into PCB->Reg[8]
Data collection for performance metrics
PCB->waitingTime = PCB->waitingTime + CLOCK - PCB->queueEnterClock;
Total_waiting_time = Total_waiting_time + PCB->waitingTime ;
CLOCK = CLOCK + PCB->CPUburst;
Total_turnaround_time = Total_turnaround_time + CLOCK;
Total_job = Total_job + 1;
Free PCB. Since there is no more CPUburst or I/O burst, this process is terminated here! Otherwise, it will be put in a ready or waiting queue.
Finally, print the perfromance metrics mentioned before: 
Total_waiting_time / Total_job,
Total_turnaround_time / Total_job,
Total_job / CLOCK
For each input file, copy/paste your screen output into a textfile (say output1.txt)
Deliverables
For TA to check off that you completed this recitation, remove executables and temp files (if any) from RecC1 (so just leave .c, makefile, input output files) then zip and submit the whole directory of RecC1 through BB Learn: CS 3733 --> Recitation Exercices -->  Recit C1.
Prepared by Turgay Korkmaz