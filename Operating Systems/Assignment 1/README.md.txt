CS 3733 Operating Systems Assignment 1
You are required to submit your work through UTSA Learn (f. Blackboard or BB)  !!! No e-mail submissions !!!

!!!! Please carefully check the DUE DATE on BB Learn !!!!

!!!! NO LATE SUBMISSION WILL BE ACCEPTED !!!


Overview
This assignment is related to process scheduling, but you do not have to know anything about process scheduling to do this assignment. The connection of this assignment to process scheduling will become clear in Assignment 2. 

You will be given an input sequence of exactly 7 integers. From this you will produce two output strings consisting of the letters R, w and r. You will also produce two integer values giving the number of times r occurs in the first string and the number of times r occurs in the second string. Lastly you will produce two floating point numbers. The first of these is the average of the two output integers and the second is the total number of R's in the two strings divided by the length of the longer string. 

You will write a single C program that takes the 7 input values as command line parameters. The program should start by checking that there are exactly 7 parameters and exit with an appropriate error message otherwise. If the number of command line parameters is correct, the program will print your name on a line in the form:
Assignment 1 program was written by ...
and then output 7 input values.
It will then display 5 additional lines: a blank line, a heading, the two output strings (the second directly under the first) and the four numeric values. 

Produce a single makefile for compiling all of the programs in this assignment. A sample makefile can be found here. 

In writing your programs, follow the programming style guidelines here. And include comments so we can easily understand and follow your logic. 

Make sure you understand the statement of the each part before writing any code for that part. For each part you will be given information about how to produce the output from the input sequence. 

You will run the program with appropriate input of your choosing to test to see if it is working. Save the output generated to be handed in with your assignment. 

You will produce two source files, assign1.c and pslibrary.c. The first will contain your main program. The second will contain functions implementing most of the assignment. In each part you will add to the source files keeping the previous capabilities. 

Part 0:
This is just to get you started. 
Create a directory called assign1 for this assignment under cs3733. 
Write a main program called assign1-0.c under assign1. 

This program takes exactly 7 integer command line parameters. It should check for the correct number of command line parameters, assume that all are integers, print a line containing your name and a line containing the values of the parameters. The output should be in the form:
Assignment 1 program was written by FirstName LastName
inputs: 0 2 4 6 7 8 9
If the number of parameters is incorrect, print an appropriate message and exit. 

The main program should then create two arrays of characters that will be large enough to hold the character string you will be creating. The maximum size of any of the strings will be the sum of the last six command line parameters. If an error occurs in creating these arrays, exit the program with an appropriate error message. Otherwise call two functions, one to create the strings and one to print them out as follows: 
void part0(char *s1, char *s2); 
void display(char *heading, char *s1, char *s2);


These two functions should be put in the file pslibrary.c. Put prototypes for these in pslibrary.h and have assign1-0.c include pslibrary.h. 

For this part of the assignment use the heading: "Part 0\n". The part0 function will just copy the following strings into the two parameters: RRwwwwwRRRRRRRRR and rrRRRRwwwwwwwwrrRRRRRRR and return. Note that part0 ignores all of the command line parameters. Call the program with parameters that are large enough so that the program will allocate enough space for these strings. 

The display function that you write for this part will be used in the next part of this assignment and in future assignments.The display function prints only to standard out and does the following:
Print a blank line to standard output.
Print the heading.
Print the first string on its own line.
The first string is the second parameter to display. You may assume that the heading ends with a new line so that the first string is printed at the start of a line. After printing this string, print a newline so that next string starts directly below it.
Print the second string on its own line.
After writing the string to standard output, output a newline.
Print 4 numeric values all on a single line, separating consecutive values with a single blank.
The number of 'r' characters in the second parameter.
The number of 'r' characters in the third parameter.
The average of these two number, displayed with one decimal place.
A floating point number number displayed with 5 decimal places. This values is the total number of 'R' characters in the second and third parameters divided by the length of the longer of these two parameters.
Run Part 0 and save the output generated as output-part0.txt 

Note: When you run Part 0, make sure that the command line parameters are large enough so that there is enough room for the strings. 

Part 1:
Write a function in pslibrary.c called fcfsa that takes two string parameters and 6 integer parameters. It fills in the strings for the first two parameters as described as follows. Suppose the function is called with
fcfsa(s1, s2, x1, y1, z1, x2, y2, z2);
The first string, s1, will consist of a x1 R's, followed by y1 w's, followed by 0 or more r's, followed by z1 R's.
The number of r's will be described later. 

The second string, s2, will be consist of x1 r's, followed by x2 R's, followed by y2 w's, followed by 0 or more r's, followed by z2 R's. 

The number of r's in each string will determined by the following conditions:
The two strings will not have R's in the same position.
No string will have an r in the position that the other string has an r or w.
The first string will have the smallest number of r's that will allow it to satisfy conditions a) and b).
The second string will have the smallest number of r's that will not contradict a), b), or c).
Copy assign1-0.c into assign1.c and have assign1.c call fcfsa using the last 6 integer parameters (ignore the first integer parameter) instead of calling part0 It will then call display.

Example 1:
With the input sequence: 0 4 2 7 3 6 5
the output generated by display should be:
RRRRwwrRRRRRRR
rrrrRRRwwwwwwrRRRRR
1 5 3.0 1.00000 

Example 2:
With the input sequence: 0 4 9 5 6 3 7
the output generated by display should be:
RRRRwwwwwwwwwRRRRR
rrrrRRRRRRwwwrrrrrRRRRRRR
0 9 4.5 0.88000 

Test your program with inputs you have developed. Then run the program with each of the following six tests. For each, save the output in a file and label each one as Test-1.txt, Test-2.txt, Test-3.txt, Test-4.txt, Test-5.txt, or Test-6.txt. 

Test 1: 3 8 7 3 6 3 2.
Test 2: 3 8 7 3 6 7 2.
Test 3: 4 8 7 3 6 1 2.
Test 4: 3 3 3 4 2 1 2.
Test 5: 3 3 2 3 2 1 2.
Test 6: 3 5 2 5 4 1 1.
These files will be turned in with your assignment. 

A Final Test:
Get a copy of this program.
Compile this program with you pslibrary as follows:
cc -o runalla runalla.c pslibrary.c.
Then execute runalla. It should create a file called fcfsa.all.
Execute:
ls -l fcfsa.all
wc fcfsa.all
md5sum fcfsa.all
and include the output of these treecommands in your REPORT.txt.
Since the the fcfsa.all file is large (which should have 2,000,001 lines and 2,000,003 words),
you should delete it after you have saved the output in your REPORT.txt.
Note: if you are getting segmentation fault when executing runall, then something is wrong in your fcfsa() function under some cases! Double chek your function fcfsa()!
REPORT: 
Create a REPORT.txt file to answer the following questions: 

1. List all of the people that you have collaborated with on this assignment. For each person indicate the level of collaboration (small, medium, large). Also write a few sentences describing what was discussed. Indicate whether you were mainly giving help or receiving help. 

2. Do you think everything you did is correct? ..... 

3. If not, give a brief description of what is working and what progress was made on the part that is not working. 

4. Comments (e.g., what were the challenges, how to make this assignment more interesting etc.): 

5. Program output: (if you print anything on the screen, then copy/paste it here. don't copy/paste output files here)
SUBMISSION: 
Go to cs3733 and zip (or tar) the whole directory of assign1 as a single file abc123-assign1.zip, where abc123 should be replaced with your abc123 ID. This is very important for TA to get all files at once.
You need to submit this single zip (or tar) file through UTSA Learn (Blackboard or BB Learn)  !!! No e-mail submissions !!!

GRADING:
This assignment is worth 40 points. To receive full credit for this assignment, you must submit it through BB Learn before the due date and it must be in the format as described above. 
Based on materials provided by Prof. Steve Robbins.