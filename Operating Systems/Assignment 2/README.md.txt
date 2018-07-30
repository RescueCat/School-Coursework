CS 3733 Operating Systems: Assignment 2
You are required to submit your work through UTSA Learn (aka. Blackboard or BB Learn) !!! No e-mail submissions !!!

!!!! Please carefully check the DUE DATE on BB Learn !!!!

!!!! NO LATE SUBMISSION WILL BE ACCEPTED !!!


Overview
This assignment is a continuation of Assignment 1. Make an assign2 directory and copy all of your files from assignment 1 into this directory. Make sure your program runs correctly from this directory. You will be modifying these files. 

Problem description in terms of process scheduling
Consider two processes, each with two CPU bursts with one I/O burst in between. Process 1 has a CPU burst of x1 units followed by an I/O burst of y1 units followed by a second CPU burst of z1 units. Process 2 has a CPU burst of x2 units followed by an I/O burst of y2 units followed by a second CPU burst of z2 units. Suppose that Process 1 arrives in the ready queue just before Process 2 and there are no otherprocesses in the system. For each of the scheduling algorithms draw a Gantt charts showing the state of each of the two processes. Use the letter R to represent the running state, the letter w for the waiting state and the letter r for the ready state. Calculate the two waiting times, the average waiting time and the CPU utilization. (Break any ties by having process 1 run first.) 

Part 1 of assignment 1 describes an algorithm that is similar, but possibly not identical to the FCFS algorithm, where the last 6 input parameters are x1, y1, z1, x2, y2, and z2. The numbers displayed are the waiting times for process 1 and process 2, the average waiting time, and the cpu utilization. This version of the algorithm always chooses process 1 if both processes become ready at the same time. 

Create a directory called assign2 for this assignment under cs3733. 
Write all your programs under assign2. 

Part 1

In this part of the assignment you will write your fcfs program using a state machine design. A state machine has a state (the values of the variables) which changes over time. At each time step the state changes to a new state. The new state depends only on the old one and the input values. 

In this case, the state of the system is the state of the two processes, including information about all of their remaining CPU and I/O bursts. Use this code as a prototype for your fcfs function. Insert the appropriate code so that it behaves like the fcfs algorithm. It should usually produce the same strings as your Assignment 0. The protoype may handle some cases that are not related to fcfs, such as a quantum. You may delete the unncessary code. 

Run your program on the two examples given in Assignment 1 and the 6 tests. Your results for all of these tests should be the same as for Assignment 1. 

Part 2
Implement the SJF algorithm (non-preemptive). Again, ignore the first input parameter. Do this by putting the function:
sjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2);
in pslibrary.c. Add two lines to assign1.c to call this and display. Use the heading: "SJF\n". Implement this by modifying your fcfs code or the prototype. 

Part 3
Implement the PSJF algorithm. That is, write the function:
psjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2); 
in pslibrary.c. Add two lines to assign1.c to call this and display. Use the heading: "PSJF\n". Implement this by modifying your fcfs code or the prototype. 

Part 4
Implement the Round Robin algorithm.
That is, write the function:
rr(char *s1, char *s2, int q, int x1, int y1, int z1, int x2, int y2, int z2);
in pslibrary.c. Add two lines to assign1.c to call this and display. Use the heading: "RR\n". Implement this by modifying your fcfs code or the prototype. 
Note: in this case the first input parameter is the quantum and the others will be as before. 

Test your program with inputs you have developed. Convince yourself that the program is running correctly. 

Now run your program on the 12 tests (all 4 algoritms) from quiz 4. Use a quantum of 3 for all of the tests, except test number 3 which has a quantum of 4. Fill in your results on the program output part of REPORT.txt. 

Note on breaking ties:
Processes can enter the ready queue when they first arrive, when their quantum expires, or when their I/O completes. When the RR algorithm must choose the oldest process from the ready queue it needs a way to break ties. For our algorithms, we break a tie by having process 1 run before process 2. Make sure you understand this and make sure your solution works with the following input: 3 1 1 4 1 3 1 

Part 5
As a final test, get a copy of runall.c here. 
Look at the source code and understand it.
Compile it with your pslibrary and run the program.
It should take less than a minute to complete and generate 4 files, each of about 40 megabytes and having the extension .all.
Make sure you have no other files with this extension in your directory and execute:
ls -l *.all
wc *.all
md5sum *.all
Include the output generated with your assignment.
Each of the files should have 2,000,001 lines and 2,000,003 words.
You should delete these large files after you write the output of md5sum on the program output part of REPORT.txt . 

Note: if you are getting segmentation fault when executing runall, then something is wrong in the functions you implemented above! Double chek your functions!
REPORT: 
Create a REPORT.txt file to answer the following questions: 

1. List all of the people that you have collaborated with on this assignment. For each person indicate the level of collaboration (small, medium, large). Also write a few sentences describing what was discussed. Indicate whether you were mainly giving help or receiving help. 

2. Do you think everything you did is correct? ..... 

3. If not, give a brief description of what is working and what progress was made on the part that is not working. 

4. Comments (e.g., what were the challenges, how to make this assignment more interesting etc.): 

5. Program output: ((if you print anything on the screen, then copy/paste it here. don't copy/paste output files here)
SUBMISSION: 
Go to cs3733 and zip (or tar) the whole directory of assign2 as a single file abc123-assign2.zip, where abc123 should be replaced with your abc123 ID. This is very important for TA to get all files at once.
You need to submit this single zip (or tar) file through UTSA Learn (Blackboard or BB Learn)  !!! No e-mail submissions !!!

GRADING:
This assignment is worth 60 points. To receive full credit for this assignment, you must submit it through BB Learn before the due date and it must be in the format described above. 