CS 3733 Operating Systems, Recitation Session B
Log on to your Linux Account.
Create a RecB subdirectory under cs3733 and do all your work under RecB.
-----------------------------------------
Access the USP web site: http://classque.cs.utsa.edu/usp/
Click on the Programs link.
Download the (uncompressed) tar file for chapter 9.
Untar the files into your RecB directory.
Run the convertlinux script to modify the makefile.
Compile all of the programs from Chapter 9 of USP by executing make.
Execute the program badtiming
This should print out two lines.
Read pages 302 through 305 of USP. You may stop reading after the answer to Exercise 9.4 on the top of page 305. You can find these pages online here.
Look at the output produced by your run of badtiming and see that it agrees with the answer to Exercise 9.4.
Modify the function in functiontotime.c so that the loop is 20 times longer. That is, replace the 1 with a 2 and add a zero at the end of the big number. (Don't make it any larger or it will overflow the integer.)
Run badtiming again and see that even though it takes more than a second to run, the start and end times are displayed as the same value.
Copy badtiming.c into goodtiming.c and modify the makefile so that it also compiles goodtiming.
Run goodtiming and see that it still produces the same type of output as badtiming.
Modify goodtiming so that it produces output in the same format but prints out the correct start and end times. However, do not put any additional code between the two calls to time. Otherwise, we will be timing the new code, and not just the call to function_to_time.
Deliverables
For TA to check off that you completed this recitation, submit the screenshots and goodtiming.c through BB Learn for CS 3733 under Recitation Exercices  Recit B
