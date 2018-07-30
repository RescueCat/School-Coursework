/**********************************************************************
    cs3743p2.h
    Copyright 2018 Larry Clark, this code may not be copied to any other website
Purpose:
    Defines constants for
        return codes
        maximum record size
    Defines typedefs for
        HashHeader - describes the format of the hash file
        Book - describes the contents of a book record
    Prototypes
        functions defined in the driver
        functions the students must code
Notes:
    
**********************************************************************/

#include <stdio.h>
#define TRUE                1
#define FALSE               0
#define RC_OK               0
#define RC_FILE_EXISTS      1   // file already exists
#define RC_REC_EXISTS       2   // record already exists
#define RC_REC_NOT_FOUND    3   // record not found
#define RC_FILE_NOT_FOUND   4   // file not found or invalid info record
#define RC_BAD_REC_SIZE     5   // invalid record size in info record
#define RC_LOC_NOT_FOUND    6   // Location not found for read
#define RC_LOC_NOT_WRITTEN  7   // Location not written for write
#define RC_SYNONYM          8   // Synonym exists at the specified location
#define RC_NOT_IMPLEMENTED  9   // Not implemented
#define RC_INVALID_PARM     99

#define MAX_REC_SIZE        500

// HashHeader structure for record at RBN 0. 
// Notes:
//     - do NOT write the sizeof this record.  Instead,
//       use the iRecSize.
//     - it contains filler on the end to make certain
//     - it is as big as a hash record.
typedef struct
{
    int  iNumPrimary;       // Number of records defined for Primary 
                            // area.  (This isn't the number of
                            // records currently in the Primary Area.)
    int  iHighOverflowRBN;  // Highest record used in the overflow area
    int  iRecSize;          // Size in bytes for each record in the
                            // hash file
    char sbFiller[MAX_REC_SIZE];     // This should be set to zeros.  It is 
                            // here to make certain the Info record is 
                            // at least as big as the data.
} HashHeader;
typedef struct 
{
    int  iNextChain;        // RBN of next synonym
    char szBookId[12];      // Individual Book Id (not ISBN since
                            // multiple copies have the same value)
    char szTitle[40];       // Title
    char szPublisher[12];   // Book publisher
    char szSubject[12];     // Subject (e.g., PgmLang, Database)
    int  iPages;            // Number of pages in the book
} Book;

// Driver functions that the student can use
int hashDump(char szHashContent[], char szFileNm[]);
int hash(char szKey[], HashHeader *pHashHeader);
void printBook(Book *pBook);
void errExit(const char szFmt[], ... );

// Functions written by the student
int hashCreate(char szFileNm[], HashHeader *pHashHeader);
FILE *hashOpen(char szFileNm[], HashHeader *pHashHeader);
int readRec(FILE *pFile, int iRBN, void *pRecord, int iRecSize);
int writeRec(FILE *pFile, int iRBN, void *pRecord, int iRecSize);
int bookInsert(FILE *pFile, HashHeader *pHashHeader, Book *pBook);
int bookRead(FILE *pFile, HashHeader *pHashHeader, Book *pBook);
int bookUpdate(FILE *pFile, HashHeader *pHashHeader, Book *pBook);
int bookDelete(FILE *pFile, HashHeader *pHashHeader, Book *pBook); 
