CS 3733 Operating Systems, Recitation Session E
In this session you will experiment with compiling and running programs that use threads under both Linux and Solaris.
Log on to your Linux Account.
Create a RecE directory under cs3733 and do all your work under RecE.
-----------------------------------------
Put copies of the following programs in your RecE directory:
makefile
getsizeschild.c
getsizesthread.c
Review these and make sure you understand what they do. Compile the programs using make.
In the following parts of the recitation you will be answering questions about the results of the runs you do. Put the answers in a file called answersE.txt in your RecE directory. Number each answer with the corresponding part of the recitation. For example, the first answer should be labeled with a 6. The first line of this file should contain your name. You will only be graded on having completed answers to these questions, not on the quality of your answers.
Run the getsizeschild program by executing:
     make runchild
Which of the values were reported correctly? Explain why each of the incorrect ones were incorrect.
How would the answer above change if the parent waited for the child before using the results?
Run the getsizesthread program by executing:
     make runthread
Which of the values were reported correctly? Explain why each of the incorrect ones were incorrect.
Comment out the four lines in getsizesthread.c that correspond to the pthread_join. Explain the results when you compile and run the program again and explain why the results should or should not be the same as before.
Remove the comments and compile and run the program again. Confirm that the results are what is expected.
Remove the reference to LIBTHREAD in the compile line for getsizesthread in the makefile.
Execute
     make clean
     make
If the program compiles, run it again. Describe the results.
Put back the reference to LIBTHREAD in the makefile. Compile again and convince yourself that the program is working correctly.
Check that your file answersE.txt has answers labeled for parts 6, 7, 8, 9, and 12.
Deliverables 
For TA to check off that you completed this recitation, submit the screenshots and answersE.txt file through BB Learn for CS 3733 under Recitation Exercices  Recit E Please zip directories....