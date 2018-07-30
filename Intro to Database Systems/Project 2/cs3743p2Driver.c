/**********************************************************************
    cs3743p2Driver.c by Larry Clark
    Copyright 2018 Larry Clark, this code may not be copied to any 
    other website.
Purpose:
    This program demonstrates a Hash File which uses overflow chaining.
    It uses a stream input command file to test the various 
    functions written by the students.
Command Parameters:
    p2 < infile > outfile
    The stream input file contains commands.  There are commands 
    which specify create, insert, read, delete, update, and dump.
   
    Commands in the input file:
    
    * comment       
        This is just a comment which helps explain what is being tested.
    
    CREATE BOOK fileName numPrimary   
        Create the specified hash file if it doesn't already exist
        using hashCreate.
        The file will have numPrimary records in the primary area.
        Record 0 contains information about this hash file.
        The size of each record is the size of a Book structure.
        
    OPEN BOOK fileName 
        Opens the specified file using hashOpen.  Place the returned
        FILE pointer in the driver's HashFile array.
    INSERT BOOK bookId,title,publisher,subject,pages
        Uses sscanf to get those attributes and populate a BOOK structure.
        It invokes bookInsert to insert the book into the hash file.
    READ BOOK bookId
        Invokes bookRead to read the book from the hash file.
    UPDATE BOOK bookId,title,publisher,subject,pages
        Uses sscanf to get those attributes and populate a BOOK structure.
        It invokes bookUpdate to update the book in the hash file.
    DELETE BOOK bookId
        Invokes bookDelete to delete the book in the hash file.  This will leave
        an empty entry.  This is for extra credit.
    DUMP BOOK fileName
        Prints the contents of the specified file.
    NUKE BOOK fileName
        Removes the specified file.

Results:
    All output is written to stdout.
    Prints each of the commands and their command parameters.  Some of the commands
    print information:  
        CREATE - prints the record size
        INSERT - prints the primary RBN
        READ   - prints the book information (if found)
        DUMP   - dumps the file's contents
Returns:
    0       Normal
    99       Processing Error

Notes:
   
**********************************************************************/
// If compiling using visual studio, tell the compiler not to give its warnings
// about the safety of scanf and printf
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include "cs3743p2.h"

#define MAX_TOKEN_SIZE 50		// largest token size for tokenizer
#define MAX_BUFFER_SZ 200       // size of input buffer for command file
#define ERROR_PROCESSING 99

// prototypes only used by the driver
void processCommands(FILE *pfileCommand);
int getSimpleToken(char szInput[], const char szDelims[]
    , int *piBufferPosition, char szToken[]);
void printRC(int rc);

int main(int argc, char *argv[])
{
    // Process commands for manipulating hash files
    processCommands(stdin);
    printf("\n");
    return 0;
}

/******************** processCommands **************************************
    void processCommands(FILE *pfileCommand)
Purpose:
    Reads the Command file to process commands.  There are several types of
    records (see the program header for more information).
Parameters:
    I FILE *pfileCommand    command stream input
Notes:
    This calls functions inside:
        cs3723p2 
**************************************************************************/
void processCommands(FILE *pfileCommand)
{
    // variables for command processing
    char szInputBuffer[MAX_BUFFER_SZ+1];    // input buffer for a single text line
    char szCommand[MAX_TOKEN_SIZE + 1];     // command
    int bGotToken;                          // TRUE if getSimpleToken got a token
    int iBufferPosition;                    // This is used by getSimpleToken to 
                                            // track parsing position within input buffer
    int iScanfCnt;                          // number of values returned by sscanf
    int rc;                                 // return code from functions
    Book book;                              // Book structure used by functions
    HashHeader hashHeader;                  // hash file header record
    char szHashContent[11];                 // content type for hash file (e.g., BOOK)
    char szFileNm[31];                      // Hash File Nm
    FILE *pBookFile;                        // file pointer to Book hash file

    //  get command data until EOF
    while (fgets(szInputBuffer, MAX_BUFFER_SZ, pfileCommand) != NULL)
    {
        // if the line is just a line feed, ignore it
        if (szInputBuffer[0] == '\n')
            continue;

        // get the command
        iBufferPosition = 0;                // reset buffer position
        bGotToken = getSimpleToken(szInputBuffer, " \n\r", &iBufferPosition, szCommand);
        if (! bGotToken)
            errExit("Invalid stream input record:\n%s", szInputBuffer);

        // see if the command is a comment
        if (szCommand[0]== '*')
        {
            printf("%s", szInputBuffer);
            continue;       // it was just a comment
        }
        printf(" >> %s", szInputBuffer);

        // Process each type of input command
        if (strcmp(szCommand, "CREATE") == 0)
        { // CREATE BOOK fileName numPrimary 
            iScanfCnt = sscanf(&szInputBuffer[iBufferPosition]
                , "%10s %30s %d"
                , szHashContent
                , szFileNm
                , &hashHeader.iNumPrimary);
            if (iScanfCnt <  3)
                errExit("Invalid input:\n%s", szInputBuffer);
            memset(hashHeader.sbFiller, 0, sizeof(hashHeader.sbFiller));
            hashHeader.iRecSize = sizeof(Book);
            printf("    Record size is %d\n", hashHeader.iRecSize);
            rc = hashCreate(szFileNm, &hashHeader);
            if (rc != 0)
                printRC(rc);
        }
        else if (strcmp(szCommand, "OPEN") == 0)
        { // OPEN BOOK fileName 
            iScanfCnt = sscanf(&szInputBuffer[iBufferPosition]
                , "%10s %30s"
                , szHashContent
                , szFileNm);
            if (iScanfCnt < 2)
                errExit("Invalid input:\n%s", szInputBuffer);
            hashHeader.iRecSize = sizeof(Book);
            pBookFile = hashOpen(szFileNm, &hashHeader);
            if (pBookFile == NULL)
                printf("    **** ERROR: File does not exist or has invalid format: '%s'\n", szFileNm);
        }
        else if (strcmp(szCommand, "INSERT") == 0)
        { // INSERT BOOK bookId,title,publisher,subject,pages
            iScanfCnt = sscanf(&szInputBuffer[iBufferPosition]
                , "%10s %11[^,],%39[^,],%11[^,],%11[^,],%d"
                , szHashContent
                , book.szBookId
                , book.szTitle
                , book.szPublisher
                , book.szSubject
                , &book.iPages);
            if (iScanfCnt <  6)
                errExit("Invalid input:\n%s", szInputBuffer);
            printf("    Hash RBN is %d\n", hash(book.szBookId, &hashHeader));
            rc = bookInsert(pBookFile,&hashHeader,&book);
            if (rc != 0)
                printRC(rc);
        }
        else if (strcmp(szCommand, "UPDATE") == 0)
        { // UPDATE BOOK bookId,title,publisher,subject,pages
            iScanfCnt = sscanf(&szInputBuffer[iBufferPosition]
                , "%10s %11[^,],%39[^,],%11[^,],%11[^,],%d"
                , szHashContent
                , book.szBookId
                , book.szTitle
                , book.szPublisher
                , book.szSubject
                , &book.iPages);
            if (iScanfCnt <  6)
                errExit("Invalid input:\n%s", szInputBuffer);
            rc = bookUpdate(pBookFile,&hashHeader,&book);
            if (rc != 0)
                printRC(rc);
        }
        else if (strcmp(szCommand, "READ") == 0)
        { // READ BOOK bookId
            iScanfCnt = sscanf(&szInputBuffer[iBufferPosition]
                , "%10s %11s"
                , szHashContent
                , book.szBookId);
            if (iScanfCnt <  2)
                errExit("Invalid input:\n%s", szInputBuffer);
            rc = bookRead(pBookFile,&hashHeader,&book);
            if (rc != 0)
                printRC(rc);
            else
            {
                printf("    ..");  //indent like the DUMP command
                printBook(&book);
            }

        }
        else if (strcmp(szCommand, "DELETE") == 0)
        { // DELETE BOOK bookId
            iScanfCnt = sscanf(&szInputBuffer[iBufferPosition]
                , "%10s %11s"
                , szHashContent
                , book.szBookId);
            if (iScanfCnt <  2)
                errExit("Invalid input:\n%s", szInputBuffer);
            rc = bookDelete(pBookFile,&hashHeader,&book);
            if (rc != 0)
                printRC(rc);
        }
        else if (strcmp(szCommand, "DUMP") == 0)
        { // DUMP BOOK fileName
            iScanfCnt = sscanf(&szInputBuffer[iBufferPosition]
                , "%10s %30s"
                , szHashContent
                , szFileNm);
            if (iScanfCnt < 2)
                errExit("Invalid input:\n%s", szInputBuffer);
            // Flush the Hash File so that hashDump can see it
            fflush(pBookFile);
            rc = hashDump(szHashContent, szFileNm);
            if (rc != 0)
                printRC(rc);
        }
        else if (strcmp(szCommand, "NUKE") == 0)
        { // NUKE BOOK fileName
            iScanfCnt = sscanf(&szInputBuffer[iBufferPosition]
                , "%10s %30s"
                , szHashContent
                , szFileNm);
            if (iScanfCnt < 2)
                errExit("Invalid input:\n%s", szInputBuffer);
            rc = remove(szFileNm);  // Ignore the rc
        }
        else
            printf("   *** Unknown command in input: '%s'\n", szCommand);
    }
}
/******************** hash **************************************
  int hash(char szKey[],HashHeader *pHashHeader)
Purpose:
    Hashes a key to return an RBN between 1 and pHashHeader->iNumPrimary 
    (inclusive).
Parameters:
    I   char szKey[]              key to be hashed
    I   HashHeader *pHashHeader   hash header structure
Returns:
    Returns a hash value into the primary area.  This value is between 1
    and pHashHeader->iNumPrimary
Notes:
    - Primary area of the hash table has subscripts from 1 to 
      pHashHeader->iNumPrimary.
    - Overflow area begins with pHashHeader->iNumPrimary + 1.
    - The hash function is average at spreading the values.  
**************************************************************************/
int hash(char szKey[],HashHeader *pHashHeader)
{
    int iHash = 0;
    int i;
    for (i = 0; i < (int) strlen(szKey); i++)
    {
        iHash += szKey[i];
    }
    // restrict it to the primary area
    iHash = iHash % abs(pHashHeader->iNumPrimary) +1; 
    return iHash;
}
/******************** hashDump **************************************
  int hashDump(char szHashContent[], char szFileNm[]))
Purpose:
    Prints the contents of the specified hash file. 
Parameters:
    I   char szHashContent[]          hash file content type
    I   char szFileNm[]               hash file name
Returns:
    RC_OK - normal
    RC_FILE_NOT_FOUND - file not found
    RC_BAD_REC_SIZE - bad record size
Notes:
    - Primary area of the hash table has subscripts from 1 to 
      pHashHeader->iNumPrimary.
    - Overflow area begins with pHashHeader->iNumPrimary + 1.
**************************************************************************/

int hashDump(char szHashContent[], char szFileNm[])
{
    struct Record
    {
        int iNextChain;
        char sbBuffer[MAX_REC_SIZE];
    } record;

    HashHeader hashHeader;
    long lRBA;
    long lRecNum;
    int rcFseek;
    FILE *pHash;
    // open the hash file
    hashHeader.iRecSize = sizeof(Book);
    pHash = hashOpen(szFileNm, &hashHeader);
    if (pHash == NULL)
        return RC_FILE_NOT_FOUND;

    // print the Hash Header
    printf("    Primary=%d, HighOverflow=%d, RecSize=%d\n"
        , hashHeader.iNumPrimary
        , hashHeader.iHighOverflowRBN
        , hashHeader.iRecSize);
    if (hashHeader.iRecSize < sizeof(Book))
        return RC_BAD_REC_SIZE;

    // locate the first record
    lRecNum = 1;
    lRBA = lRecNum*hashHeader.iRecSize;
    rcFseek = fseek(pHash, lRBA, SEEK_SET);
    assert(rcFseek == 0);
    while(fread(&record, hashHeader.iRecSize, 1L, pHash)==1)
    {
        if (lRecNum == hashHeader.iNumPrimary+1)
            printf("Overflow:\n");
        if (lRecNum > hashHeader.iNumPrimary
            || record.iNextChain != 0 || record.sbBuffer[0] != '\0')
        {
            printf("    %2ld", lRecNum);
            printBook((Book *) &record);
        }
        lRecNum += 1;
    }
    fclose(pHash);
    return RC_OK;
}
/******************** printBook **************************************
    void printBook(Book *pBook)
Purpose:
    Prints the book information for one book.
Parameters:
    I Book *pBook       // Book info
**************************************************************************/
void printBook(Book *pBook)
{
    printf(" Next=%d\n", pBook->iNextChain);
    printf("        %-11s %-11s %-11s %4d %s\n"
    , pBook->szBookId
    , pBook->szPublisher
    , pBook->szSubject
    , pBook->iPages
    , pBook->szTitle);
}

/******************** printRC **************************************
    void printRC(int rc)
Purpose:
    For a non-zero RC, it prints an appropriate message
Parameters:
    I int rc;           // return code value which is an error if
                        // non-zero

**************************************************************************/
void printRC(int rc)
{
    char *pszMsg;           // pointer to an error message
    char szBuf[100];        // buffer for building an error message
    switch(rc)
    {
        case RC_OK:
            return;
        case RC_FILE_EXISTS:
            pszMsg = "file already exists";
            break;
        case RC_REC_EXISTS:
            pszMsg = "record already exists";
            break;
        case RC_REC_NOT_FOUND:
            pszMsg = "record not found";
            break;
        case RC_INVALID_PARM:
            pszMsg = "invalid parameter";
            break;
        case RC_FILE_NOT_FOUND:
            pszMsg = "file not found or invalid info record";
            break;
        case RC_BAD_REC_SIZE:
            pszMsg = "invalid record size in info recordd";
            break;
        case RC_LOC_NOT_FOUND:
            pszMsg = "Location not found for read";
            break;
        case RC_LOC_NOT_WRITTEN:
            pszMsg = "Location not written for write";
            break;
        case RC_SYNONYM:
            pszMsg = "Synonym exists at the specified location";
            break;
        case RC_NOT_IMPLEMENTED:
            pszMsg = "Function not implemented";
            break;
        default:
            sprintf(szBuf, "unknown return code: %d", rc);
            pszMsg = szBuf;
    }
    printf("    **** ERROR: %s\n", pszMsg);
}
/******************** getSimpleToken **************************************
 int getSimpleToken(char szInput[], char szDelims[]
     , int *piBufferPosition, char szToken[]) 
Purpose:
    Returns the next token in a string.  The delimiter(s) for the token is  
    passed as a parameter.  To help positioning for a subsequent call, it 
    also returns the next position in the buffer.
Parameters:
    I   char szInput[]          input buffer to be parsed
    I   char szDelims[]         delimiters for tokens
    I/O int *piBufferPosition   Position to begin looking for the next token.
                                This is also used to return the next 
                                position to look for a token (which will
                                follow the delimiter).
    O   char szToken[]          Returned token.  
Returns:
    Functionally:
        TRUE - a token is returned
        FALSE - no more tokens
    iBufferPosition parm - the next position for parsing
    szToken parm - the returned token.  If not found, it will be an empty string.
Notes:
    - If the token is larger than MAX_TOKEN_SIZE, we return a truncated value.
**************************************************************************/

int getSimpleToken(char szInput[], const char szDelims[]
    , int *piBufferPosition, char szToken[]) 
{
    int iDelimPos;                      // found position of delim
    int iCopy;                          // number of characters to copy
    
    // check for past the end of the string
    if (*piBufferPosition >= (int) strlen(szInput))
    {
        szToken[0] = '\0';              // mark it empty
        return FALSE;                   // no more tokens
    }

    // get the position of the first delim, relative to the iBufferPosition
    iDelimPos = strcspn(&szInput[*piBufferPosition], szDelims);

    // see if we have more characters than target token, if so, trunc
    if (iDelimPos > MAX_TOKEN_SIZE)
        iCopy = MAX_TOKEN_SIZE;             // truncated size
    else
        iCopy = iDelimPos;
    
    // copy the token into the target token variable
    memcpy(szToken, &szInput[*piBufferPosition], iCopy);
    szToken[iCopy] = '\0';              // null terminate

    // advance the position
    *piBufferPosition += iDelimPos + 1;  
    return TRUE;
}

/******************** errExit **************************************
  void errExit(const char szFmt[], ... )
Purpose:
    Prints an error message defined by the printf-like szFmt and the
    corresponding arguments to that function.  The number of 
    arguments after szFmt varies dependent on the format codes in
    szFmt.  
    It also exits the program.
Parameters:
    I   const char szFmt[]      This contains the message to be printed
                                and format codes (just like printf) for 
                                values that we want to print.
    I   ...                     A variable-number of additional arguments
                                which correspond to what is needed
                                by the format codes in szFmt. 
Returns:
    Exits the program with a return code of ERROR_PROCESSING (99).
Notes:
    - Prints "ERROR: " followed by the formatted error message specified 
      in szFmt. 
    - Requires including <stdarg.h>
**************************************************************************/
void errExit(const char szFmt[], ... )
{
    va_list args;               // This is the standard C variable argument list type
    va_start(args, szFmt);      // This tells the compiler where the variable arguments
                                // begins.  They begin after szFmt.
    printf("ERROR: ");
    vprintf(szFmt, args);       // vprintf receives a printf format string and  a
                                // va_list argument
    va_end(args);               // let the C environment know we are finished with the
                                // va_list argument
    printf("\n"); 
    exit(ERROR_PROCESSING);
}
