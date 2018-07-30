#ifndef _myio_h
#define _myio_h
#include <stdio.h>

/*
 * Function: ReadInteger
 * Usage: i = ReadInteger();
 * ------------------------
 * ReadInteger reads a line of text from standard input and scans
 * it as an integer.  The integer value is returned.  If an
 * integer cannot be scanned or if more characters follow the
 * number, the user is given a chance to retry.
 */
int ReadInteger(void);

/*
 * Function: ReadDouble
 * Usage: x = ReadDouble();
 * ---------------------
 * ReadDouble reads a line of text from standard input and scans
 * it as a double.  If the number cannot be scanned or if extra
 * characters follow after the number ends, the user is given
 * a chance to reenter the value.
 */
double ReadDouble(void);

/*
 * Function: ReadLine
 * Usage: s = ReadLine();
 * ---------------------
 * ReadLine reads a line of text from standard input and returns
 * the line as a string.  The newline character that terminates
 * the input is not stored as part of the string.
 */
char *ReadLine(void);

/*
 * Function: ReadLine
 * Usage: s = ReadLine(infile);
 * ----------------------------
 * ReadLineFile reads a line of text from the input file which
 * is already open and pointed by infile. It then reads the line,
 * dynamically allocates space, and returns the line as a string.
 * The newline character that terminates the input is not stored
 * as part of the * string.
 * The ReadLine function returns NULL if infile is at the
 * end-of-file position.
 * Note: the above ReadLine(); can simply be implemented as
 *  { return(ReadLineFile(stdin)); } */
char * ReadLineFile(FILE *file);

int getLength(char *line);


#endif
