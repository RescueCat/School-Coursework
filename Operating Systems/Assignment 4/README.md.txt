CS 3733 Operating Systems: Assignment 4 (60 points)
You are required to submit your work through UTSA Learn (aka. Blackboard or BB Learn) !!! No e-mail submissions !!!

!!!! Please carefully check the DUE DATE on BB Learn !!!!

!!!! NO LATE SUBMISSION WILL BE ACCEPTED !!!

Create a directory called assign4 for this assignment under cs3733. 
Write all your programs under assign4. 
In this assignment you will learn and practice developing a multithreaded application using both Java and C with Pthreads. So you will submit two programs!
The application you are asked to implement is from our textbook (SGG) chaper 4, namely Multithreaded Sorting Application. 
Here is the description of it for convenince: Write a multithreaded sorting program that works as follows: A list of double values is divided into two smaller lists of equal size. Two separate threads (which we will term sorting threads) sort each sublist using a sorting algorithm of your choice. The two sublists are then merged by a third thread a merging thread which merges the two sublists into a single sorted list.

Your program should take take an integer (say N)  from the command line. This number N represents the size of the array that needs to be sorted.  Accordingly, you should create an array of N double values and randomly select the values from the range of [1.0, 100.0]. Then sort them using multhithreading as described above and measure how long does it take to finish this sorting task.. For the comparision purposes, you are also asked to simply call your sort function to sort the whole array and measure how long does it take if we do not use multuthreading (basically one (the main) thread is doing the sorting job).

Here is how your program should be executed and a sample output:

> prog 1000 
Sorting is done in 10.0ms when two threads are used 
Sorting is done in 20.0ms when one thread is used 

You need to figure out how to implement this program in Java and C (Pthreads)! You need to be carefull about how to pass parameters in C and Java. For example, in C, because global data are shared cross all threads, perhaps the easiest way to set up the data is to create a global array. Each sorting thread will work on one half of this array. A second global array of the same size will also be created so that the merging thread will then merge the two sublists into this second array.  This programming project will require passing parameters to each of the sorting threads. In particular, it will be necessary to identify the starting index from which each thread is to begin sorting. You need to deal with similar issues in Java as well. In both case please do not use readily available sort functions/methods, you need to implement a simple one by yourself!
Part 1
In this part you will write your program in C with Pthreads. 
Part 2
In this part you will write your program in Java.   

Part 3
Test both programs with different values of N (1000, 5000, 10000,20000) and see how they perform. 
Make a table of your results and include it in your REPORT.txt. 
Comment on your results under two threads vs. no threading or using different languages.
Part 4 Bonus
Extend at least one of your program so it can take ahother command line parameter, T (an even integer). Then it creates T threads instead of just 2 and give 1/T of the array to each thread to sort and then merge! And see how increasing the number of threads affect the execution time. 
REPORT: 
Create a REPORT.txt file to answer the following questions: 

1. List all of the people that you have collaborated with on this assignment. For each person indicate the level of collaboration (small, medium, large). Also write a few sentences describing what was discussed. Indicate whether you were mainly giving help or receiving help. 

2. Do you think everything you did is correct? ..... 

3. If not, give a brief description of what is working and what progress was made on the part that is not working. 

4. Comments (e.g., what were the challenges, how to make this assignment more interesting etc.): 

5. Program output: (if you print anything on the screen, then copy/paste it here. don't copy/paste output files here)
SUBMISSION: 
Go to cs3733 and zip (or tar) the whole directory of assign4 as a single file abc123-assign4.zip, where abc123 should be replaced with your abc123 ID. This is very important for TA to get all files at once.
You need to submit this single zip (or tar) file through UTSA Learn (Blackboard or BB Learn)  !!! No e-mail submissions !!!

GRADING:
This assignment is worth 60 points (Correct execution of each program is 25pt and Part 3 is 10pt, if you do Part4, you will get extra 10pt bonus). To receive full credit for this assignment, you must submit it through BB Learn before the due date and it must be in the format described above. 