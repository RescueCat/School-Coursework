CS 3733 Operating Systems Assignment 0
You are required to submit your work through UTSA Learn (aka. Blackboard or BB Learn) !!! No e-mail submissions !!!

!!!! Please carefully check the DUE DATE on BB Learn !!!!

!!!! NO LATE SUBMISSION WILL BE ACCEPTED !!!

The goal of this assignment is to test whether you can write C programs, use Makefile, debug programs (compiling with -g option and using gdb and/or ddd), check memory leaks (run your program with valgrind) and finally submit your work through UTSA Learn (Blackboard or BB Learn). Please follow the below directions precisely and submit your work. These are the basic steps that you will follow for all the other assignments in this course.
Part 1:
For this course, create a directory called cs3733 and do all your work under that directory.

For each assignment, create a directory under cs3733. For this assignment, call it assign0 

Implement the following library and driver programs under assign0: 
Your library will be consisting of myio.h and myio.c. The function prototypes as well as more explanations are listed in myio.h. Please download it and accordingly implement the exported functions in myio.c. Basically, you are asked to develop a simple I/O library which exports a few functions to simplify the reading of an integer, a double, and more importantly a string (whole line). In contrast to standard I/O functions that can read strings (e.g., scanf with "%s", fgets) into a given static size buffer, your function should read the given input line of characters terminated by a newline character into a dynamically allocated and resized buffer based on the length of the given input line. Also your functions should check for possible errors (e.g., not an integer, not a double, illigal input, no memory etc.) and appropriately handle them. 

Then write driver programs that can simply use the functions from myio library. Specifically, you will write two driver programs: 
First one (say driver1.c) gets three command-line arguments: x y z.  It then asks user to enter x many integers, y many doubles, and z many lines. Everytime the program prints back the entered data on the stdout while printing error messages on stderr (if any). It also keeps track of the largest integer, double and the longest string. At the end, your program prints the largest intiger, double and the longest line.string that were entered.  
Second one (say driver2.c) gets two command-line arguments: input_file.txt output_file.txt. Here is a sample input_file.txt , which is a text file containig many lines. Your program reads each line and removes theextra space characters between the words and prints the new line into output_file.txt. So there will be at most one space character between the words in output_file.txt.

NOTES:
(i) In writing your programs, try to follow the programming style guidelines here. And include comments so we can easily understand and follow your logic. 
(ii) Always, make sure you release (free) the dynamically allocated memories if you allocate any memory in your programs. So, before submitting your program, run it with valgrind to see if there is any memory leakage. Also if you need to debug your program, compile your programs with -g option and then run it with gdb and/or ddd. 
(iii) Look at the end of this page for more explanation about some questions that I got from students.

Part 2:
Create a Makefile to compile your library and the driver programs.
Part 3:
Execute your driver programs a few times with different command-line arguments. For driver1, copy/paste your results into driver1_output.txt. For driver2, keep your input and output files.
REPORT: 
Create a REPORT.txt file to answer the following questions: 

1. List all of the people that you have collaborated with on this assignment. For each person indicate the level of collaboration (small, medium, large). Also write a few sentences describing what was discussed. Indicate whether you were mainly giving help or receiving help. 

2. Do you think everything you did is correct? ..... 

3. If not, give a brief description of what is working and what progress was made on the part that is not working. 

4. Comments (e.g., what were the challenges, how to make this assignment more interesting etc.): 
SUBMISSION: 
Go to cs3733 and zip the whole directory of assign0 as a single file abc123-assign0.zip, where abc123 should be replaced with your abc123 ID. This is very important for TA to get all files at once.
You need to submit this single zip (or tar) file through UTSA Learn (Blackboard or BB Learn)  !!! No e-mail submissions !!!

GRADING:
This assignment is worth 20 points. The contents of the files from Part 1 is worth 10 points of this assignment. To receive full credit for this assignment, you must submit it through BB Learn before the due date and your submitted zip file must include the other parts as described above (Makefile, outputfiles, REPORT.txt). 

Some questions I got from students: 
When implementing ReadLineFile function, student ask where to open file etc. 
This function assumes that the file is already opened and user gives the file pointer to this function. That is why you can simply implement ReadLine as char *ReadLine(){ return(ReadLineFile(stdin)); } becuase stdin is already open, right? 

In a driver application, you will simply call 
char *data;
data = ReadLine();

In the library, ReadLine() will simply have { return(ReadLineFile(stdin)); } 
So the library should still implement ReadLineFile... as said above assume that file is opened and the file pointer is passed into that function. So your implementation will read from infile pointer whatever it is pointing to (stdin or another file opend by user). It is not important in this function. 

In the first driver you will not use it directly, but in the second one you will open a file and then call ReadLineFile to read eachline from a given file and do somethign with it, like
FILE *fd;
fd=fopen(...);

char *data;
data = ReadLineFile(fd);
doSomething(data);

This makes your library general enough to work with files or stdin ...