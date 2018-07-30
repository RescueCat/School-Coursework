CS 3733 Operating Systems, Recitation Session F
In this session you will experiment with POSIX threads and mutex locks.
The questions answered in the lab include:
Are mutex locks necessary?
What is the overhead involved in using mutex locks?
Log on to your Linux Account.
Create a RecF directory under cs3733 and do all your work under RecF.
-----------------------------------------
Put the following files in this directory:
counter.c
countertest.c
gettimeofdaytiming.c
makefile
Use the makefile to compile countertest.c. This program creates a number of threads each of which calls the increment function in the counter file. We discussed the counter file in class. It contains a synchonized counter that can be incremented.
Run:
countertest 10 100
This creates 10 threads, each of which call increment 100 times. It joins the threads and then prints the expected and actual values of the count. Confirm that they are the same.
Create a log file that will contain the results of your experiments.
Adjust the second command line parameter so that countertest takes a few seconds to run. The value will probably be between 1,000,000 and 10,000,000. Confirm that it is still giving you the correct results and indicate this in your log file by showing the output generated.
Remove the synchonization from increment. Do this by commenting out the calls to pthread_mutex_lock and pthread_mutex_unlock. You will need to put in a new return statement. Run countertest again and see if this still gaves the correct answer. If it does, run it several times. What do you conclude? Put your results in the log file.
Modify increment so that count++ is replaced by:
temp = count;
temp = temp + 1;
count = temp
Run the unprotected version again and record the results. Put this in your log file with a comment about why you think you got the result you did. (It should be giving the wrong answers now. If you get the right answer, run it again several times.)
Put back the mutex calls inside of increment and run it again. Record the results with a comment in the log file explaining what happeded and why
We are now going to explore the overhead caused by the synchronization. The file gettimeofdaytiming.c is a prototype for timing. Understand how it works.
Cut and paste parts of this file into coutertest so that so that it times the running of the threads. Put the first call to gettimeofday just before the loop that creates the threads and put the second call after all threads have been joined.
Run countertest and record the results in the log file. Make several runs and indicate in the log file a typical value of the timing.
Comment out the mutex calls in increment and run this again. Put the results in your log file. Calculate the approximate number of microseconds needed for a call to the pair pthread_mutex_lock and pthread_mutex_unlock. Put the results in your log file.
Write a short conclusion in your log file about what you learned doing this lab.
Deliverables 
For TA to check off that you completed this recitation, submit the screenshots and logfile through BB Learn for CS 3733 under Recitation Exercices  Recit F Please zip directories....
