CS 3733 Operating Systems Recitation Session A
The purpose of this session is to make you familiar with the Lab environment.
Please read this if you are doing these recitations from VDI.
Log on to your Linux account.
Set up the windowing environment to your liking.
Make sure you have a cs3733 directory somewhere in your account.
Create a RecA subdirectory under cs3733 and do all your work under RecA.
-----------------------------------------
Access the USP web site: http://classque.cs.utsa.edu/usp/
Click on the Programs link.
Download the (uncompressed) tar file for chapter 5.
Untar the files into your RecA directory.
Run the convertlinux script to modify the makefile.
Compile all of the programs from Chapter 5 of USP by executing make.
Execute the program
./printaccesstest .
This should show the access time for the files in this directory.
Read pages 154 and 155 of USP starting with section 5.2.1.
You can find these pages online here.
Find the description of st_size in struct stat.
Copy printaccess.c into get_filesize.c.
Modify get_filesize.c so that the name of the function is get_filesize.
Instead of printing information, this function will return an int which is the st_size field of the structure, cast to an int.
The function does not perform any I/O.
If the call to stat fails, the function returns -1.
You should be able to remove both time.h and stdio.h from the includes.
Get a copy of the program test_get_filesize.c that is available here to test your function.
Modify the makefile to compile test_get_filesize.c and get_filesize.c to produce the executable test_get_filesize.
Run this as follows:
./test_get_filesize makefile
and convince yourself that it is working correctly.
Deliverables
For TA to check off that you completed this recitation, submit the screenshots through BB Learn for CS 3733 under Recitation Exercices  Recit A