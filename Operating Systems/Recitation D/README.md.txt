CS 3733 Operating Systems, Recitation Session D
In this session you will deal with named pipes and multiple file/pipe descriptors.
We will consider a very simple bank application with two ATMs through which customers deposit money to an account. Mainly you will implement two programs called bank.c and customer.c whose operations are desceribed below.

Log on to your Linux Account.
Create a directory called RecD under cs3733 and do all your work under RecD.
Implement bank.c
Declare and initialize TOTAL to 0.
Check the existance of two named pipes (say ATM1, ATM2). If needed, create them using mkfifo).
Open both pipes to read
In an infinite loop,
Using select, wait for either pipe to be ready (one which has data).
Read an integer (deposit) from the ready pipe and add it to TOTAL
Print TOTAL
Implement customer.c
Get the name of the named pipe from the command line
Open named pipe (argv[1]) to write
In an infinite loop,
Prompt user to enter an integer to deposit
Read an integer from standard input
If user enters an integer less than zero, break loop
Otherwise, write the given integer into the pipe
Close pipes and quit
Using makefile, compile both bank.c and cusomer.c
Open three new terminals and goto RecD in each terminal
In terminal 1, run bank
In terminal 2, run customer ATM1
In terminal 3, run customer ATM2
Randomly go into terminal 2 or 3, and enter integers and see what is printed on terminal 1.
Optinal: How about withdawing? Extend bank.c such that it can also monitor standard input along with the named pipes. Basically, it promts user to enter an integer to withdraw. When user enters an integer, bank can read it from standard input and subtract it from TOTAL. While waiting on the prompt, the pipes migt have data, so the bank go ahead and process them first then prints the prompt again.
Optinal: How would you deal with this problem if select was not avaialble? Use polling!
Deliverables 
For TA to check off that you completed this recitation, remove executables and temp files (if any) from RecD (so just leave .c and makefile) then zip and submit the whole directory of RecD through BB Learn: CS 3733 --> Recitation Exercices -->  Recit D.
Prepared by Turgay Korkmaz