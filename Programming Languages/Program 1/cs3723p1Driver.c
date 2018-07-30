/**********************************************************************
    cs3723p1Driver.c by Larry Clark
Purpose:
    This program demonstrates Storage Management software similar to
    malloc and free in C.  
Command Parameters:
    p1 <infile > outfile
    The stream input file contains commands.  There are commands 
    which specify comments, allocate memory, free memory,
    print the memory area, print the free nodes, and reset the memory. 
   
    Commands:
    * comment       
        This is just a comment which helps explain what is being tested.
    ALLOC size key string
        Size is what the requestor asks which is smaller that what will
        be allocated since an AllocNode contains additional overhead.
        Key is used as an entry in a Hash Table.
    FREE key
        Frees the memory referenced by the key
    RESET totalSize
        Initializes the heap
    PRTFREE 
        prints the free list
    PRTALL
        prints all the entries from the driver's has table
    DUMP
        dumps the memory
Results:
    All output is written to stdout.
    Prints each of the commands and their command parameters.  
    Most of the commands also print additional information.
Notes:
    1. This program uses the C++ unordered_map class to save the keys and 
       the corresponding pointers to allocated nodes.  An instance is
       created in global static memory named smHashTable.
    2. This driver program allocates memory for the student's storage
       management software to use as the heap.
    3. The student's create a separate C source file, cs3723p1.c, for
       their functions.
       
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
#include "cs3723p1.h"

#define MAX_TOKEN_SIZE 50       // largest token size for tokenizer
#define MAX_BUFFER_SZ 100       // size of input buffer

void processCommands(FILE *pfileCommand);
int getSimpleToken(char szInput[], int *piBufferPosition, char szToken[]);

#define ULAddr(addr) ((unsigned long) addr)

// If on Windows, don't use extern "C" in calling file.
// g++ compiler requires the extern "C".
#if defined(_WIN32) || defined(_WIN64)
extern void *getHash(const char *szKey);
extern void putHash(const char *szKey, void *value);
extern void eraseAll();
extern void getAll(HashMO *pHashMO);
#else
extern "C" void *getHash(const char *szKey);
extern "C" void putHash(const char *szKey, void *value);
extern "C" void eraseAll();
extern "C" void getAll(HashMO *pHashMO); 
#endif

int main(int argc, char *argv[])
{
    processCommands(stdin);
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
        hashAPi
        hexDump64
        cs3723p1 
**************************************************************************/
void processCommands(FILE *pfileCommand)
{
    // variables for command processing
    char szInputBuffer[MAX_BUFFER_SZ+1];    // input buffer for a single text line
    char szCommand[MAX_TOKEN_SIZE + 1];     // command
    int bGotToken;                          // TRUE if getSimpleToken got a token
    int iBufferPosition;                    // This is used by getSimpleToken to 
                                            // track parsing position within input buffer

    // variables used for the buffer passed to hexdump 
    int iBytesPerLine = 40;                 // number of bytes to be displayed per line
                                            // by hexDump
    int iScanfCnt;                          // number of values returned by sscanf
    
    int iBytesToSend = 0;                   // number of bytes sent to hexDump
    int iLines = 0;                         // number of lines returned from hexDump
    char sbData[MAX_DATA];
    StorageManager mgr = { 0, 0, NULL, NULL, NULL };

    SMResult smResult = { 0, "" };

    //  get command data until EOF
    while (fgets(szInputBuffer, MAX_BUFFER_SZ, pfileCommand) != NULL)
    {
        // if the line is just a line feed, ignore it
        if (szInputBuffer[0] == '\n')
            continue;

        // get the command
        iBufferPosition = 0;                // reset buffer position
        bGotToken = getSimpleToken(szInputBuffer, &iBufferPosition, szCommand);
        if (! bGotToken)
            errExit("Invalid input command line: %s", szInputBuffer);

        // see if the command is a comment
        if (szCommand[0]== '*')
        {
            printf("%s", szInputBuffer);
            continue;       // it was just a comment
        }
        memset(&smResult, '\0', sizeof(SMResult));  // in case the sm functions didn't
        printf(">>> %s", szInputBuffer);

        if (strcmp(szCommand, "RESET") == 0)
        {   // RESET totalSize
            mgr.shMinimumSize = sizeof(FreeNode)+sizeof(short);
            iScanfCnt = sscanf(&szInputBuffer[iBufferPosition]
                , "%hi"
                , &mgr.shHeapSize);
            if (iScanfCnt <  1 || mgr.shHeapSize < mgr.shMinimumSize)
                errExit("Invalid RESET command argument: %s", szInputBuffer);
            // Free the existing storage (if necessary)
            if (mgr.pBeginStorage != NULL)
                free(mgr.pBeginStorage);
            mgr.pBeginStorage = (char *) malloc(mgr.shHeapSize);
            mgr.pEndStorage = mgr.pBeginStorage + mgr.shHeapSize;
            printf("INITIALIZE:\n");
            printf("    %25s: %5d\n", "Heap Size", mgr.shHeapSize);
            printf("    %25s: %5d\n", "Minimum Node Size", mgr.shMinimumSize);
            printf("    %25s: %5ld\n", "Prefix Node Size", LEAD_OVERHEAD_SIZE);
            printf("    %25s: %5ld\n", "Tot Overhead Size",OVERHEAD_SIZE);

            smInit(&mgr);
            eraseAll();     // remove the Hash Table entries
        }
        else if (strcmp(szCommand, "ALLOC") == 0)
        {   // ALLOC size key string
            short shSize;
            char szKey[MAX_KEY_SIZE + 1];
            char szString[21];
            void *p = NULL;
            AllocNode *pAlloc;
            iScanfCnt = sscanf(&szInputBuffer[iBufferPosition]
                , "%hi %10s %20[^\n]"
                , &shSize
                , szKey
                , szString);
            if (iScanfCnt <  3 || shSize <= 0)
                errExit("Invalid ALLOC command argument: %s", szInputBuffer);
            memset(sbData, 0, sizeof(sbData));
            strcpy(sbData, szString);
            // Invoke the Storage Manager Allocate function
            p = smAlloc(&mgr, shSize, sbData, &smResult);
            // pAlloc = (AllocNode *) (((char *) p) - LEAD_OVERHEAD_SIZE);
            // If it allocated memory, save the memory address with the key
            if (p == NULL)
            {    // Did not allocate memory
                printf("\t!!! Memory not allocated\n");
                printf("\t\tsmAllocate rc=%d, %s\n"
                    , smResult.rc
                    , smResult.szErrorMessage);
            }
            else if ((char *) p < mgr.pBeginStorage
                || (char *) p >= mgr.pEndStorage )
                printf("    *** Bad Pointer returned\n");
            else
                putHash(szKey, p);  // record where it was placed
        }
        else if (strcmp(szCommand, "FREE") == 0)
        {   // FREE key
            char szKey[MAX_KEY_SIZE + 1];
            char *pUserAlloc;

            // get the key from the input
            iScanfCnt = sscanf(&szInputBuffer[iBufferPosition]
                , "%10s"
                , szKey);
            // was the key in it?
            if (iScanfCnt <  1)
                errExit("Invalid FREE command argument: %s", szInputBuffer);
            
            // get the address to free 
            pUserAlloc = (char *)getHash(szKey);
            if (pUserAlloc == NULL)
                errExit("Unexpected error in algorithm: %s", "getHash returned NULL");
            else
            {    // Invoke the Storage Manager Free function
                int iCombinedAmt = smFree(&mgr, pUserAlloc, &smResult);
                if (smResult.rc != 0)
                {
                    printf("\t\tsmFree rc=%d, %s\n"
                        , smResult.rc
                        , smResult.szErrorMessage);
                }
                else
                    printf("\t\tCombined free amount is %d\n", iCombinedAmt);
            }
        }
        else if (strcmp(szCommand, "DUMP") == 0)
        {
            int iBytesToSend;
            int iBytesPerLine = 20;
            iBytesToSend = mgr.shHeapSize;
            if (mgr.pBeginStorage == NULL)
                errExit(ERR_NULL_AREA, " DUMP command");
            printf("\tBegin Address is %p\n", mgr.pBeginStorage);
            printf("\tFree List Address is %p\n", mgr.pFreeList);
            printf("\tMinimum Amount is %d\n", mgr.shMinimumSize);
            // invoke hexDump
            hexDump((char *) mgr.pBeginStorage, iBytesToSend, iBytesPerLine);
        }
        else if (strcmp(szCommand, "PRTFREE") == 0)
        {
            if (mgr.pBeginStorage == NULL)
                errExit(ERR_NULL_AREA, " PRTFREE command");
            printf("\tBegin Address is %p\n", mgr.pBeginStorage);
            printf("\tFree List Address is %p\n", mgr.pFreeList);
            printf("\tMinimum Amount is %d\n", mgr.shMinimumSize);
            // invoke smPrintFree
            smPrintFree(&mgr);
        }
        else if (strcmp(szCommand, "PRTALL") == 0)
        {
            if (mgr.pBeginStorage == NULL)
                errExit(ERR_NULL_AREA, " PRTALL command");
            printf("\tBegin Address is %p\n", mgr.pBeginStorage);
            printf("\tFree List Address is %p\n", mgr.pFreeList);
            printf("\tMinimum Amount is %d\n", mgr.shMinimumSize);
            // invoke smPrintFree
            smPrintAll(&mgr);
            printf("\n");
        }
        else
            errExit("Invalid command: %s", szCommand);
        printf("\n");
    }
    printf("\n");
}
/******************** smPrintFree **************************************
 void smPrintFree(StorageManager *pMgr)
 Purpose:
    Traverses the free list (which is a doubly linked list) and prints 
    each free item's address, size, end size, previous pointer, 
    and next pointer. It also prints the total amount of free memory.
Parameters:
    I   StorageManager *pMgr    A pointer to a storage manager structure. 
                                This function doesn't modify that structure.
                                (It receives a pointer for consistency with
                                the other storage manager functions.)  
Returns:
    n/a 
Notes:
    - To help prevent seg fault errors, this function verifies that each 
      pointer in the doubly linked list is within the heap. 
**************************************************************************/
void smPrintFree(StorageManager *pMgr)
{
    FreeNode *pFreeNode;
    short shTotalFree = 0;
    // Get the maximum address in the heap
    FreeNode *pMaxAddr = (FreeNode *)(pMgr->pEndStorage);
    printf("\t%-8s %4s %-8s %-8s %s\n", "Address", "Size", "Prev", "Next", "End Size");

    // Traverse the free list
    for (pFreeNode = pMgr->pFreeList; pFreeNode != NULL; pFreeNode = pFreeNode->pNext)
    {
        char *pEnd;
        // See if the Free Node Pointer is valid
        if (pFreeNode < ((FreeNode *)pMgr->pBeginStorage)
            || pFreeNode >= pMaxAddr)
        {
            printf("***** Error invalid Free Node address %p\n", pFreeNode);
            return;
        }
        printf("\t%08lX %4d %08lX %08lX"
            , ULAddr(pFreeNode)
            , pFreeNode->shItemSize
            , ULAddr(pFreeNode->pPrev)
            , ULAddr(pFreeNode->pNext));
        pEnd = ((char *)pFreeNode) + pFreeNode->shItemSize;
        if (pEnd < pMgr->pBeginStorage
            || pEnd > pMgr->pEndStorage)
            printf(" Bad Item Size");
        else
        {
            short shEndSize = *((short *)(pEnd - sizeof(short)));
            printf(" %4d", shEndSize);
        }
        if (pFreeNode->pPrev != 0 && (pFreeNode->pPrev < ((FreeNode *)pMgr->pBeginStorage)
            || (pFreeNode->pPrev >= pMaxAddr)))
            printf(" Bad Prev");
        if (pFreeNode->pNext != 0 && (pFreeNode->pNext < ((FreeNode *)pMgr->pBeginStorage)
            || (pFreeNode->pNext >= pMaxAddr)))
            printf(" Bad Next");
        printf("\n");

        shTotalFree += pFreeNode->shItemSize;
    }
    printf("\t***Total %4d\n", shTotalFree);
}
/******************** smPrintAll **************************************
 void smPrintAll(StorageManager *pMgr)
 Purpose:
    Beginning at the first byte in the heap, this function advances from
    one item to the next based on the size of the items.  
    If an item has a cAF of 'A', it is an allocated item; otherwise,
    it is a free item. 
 Parameters:
    I   StorageManager *pMgr    A pointer to a storage manager structure. 
                                This function doesn't modify that structure.
                                (It receives a pointer for consistency with
                                the other storage manager functions.)  
Returns:
    n/a 
Notes:
    
**************************************************************************/
void smPrintAll(StorageManager *pMgr)
{
    FreeNode *pFreeNode;
    AllocNode *pAllocNode;
    char *pCh;
    char *pEndCh = ((char *)(pMgr->pBeginStorage)) + (pMgr->shHeapSize);
    int iTempSize;
    int iBytesToSend;
    int iBytesPerLine = 20;

    // Print each item from the beginning of the heap to the end
    printf("\t%-8s %-5s %4s\n", "Address", "Mem", "Size");
    for (pCh = pMgr->pBeginStorage; pCh < pMgr->pEndStorage; pCh += iTempSize)
    {
        char *pEnd;
        // Default it to an allocated item
        pAllocNode = (AllocNode *)pCh;
        iTempSize = pAllocNode->shItemSize;
        pEnd = ((char *)pAllocNode) + pAllocNode->shItemSize;

        // See if it is an allocated item or a free item
        if (pAllocNode->cAF == 'A')
        {   // It is an Allocated Item
            printf("\t%08lX %-5s %4d"
                , ULAddr(pAllocNode), "Alloc", iTempSize);
            if (pEnd < pMgr->pBeginStorage
                || pEnd > pMgr->pEndStorage)
                printf(" Bad Item Size");
            else
            {
                short shEndSize = *((short *)(pEnd - sizeof(short)));
                printf(" End Size=%4d", shEndSize);
            }
            printf("\n");
            iBytesToSend = iTempSize - LEAD_OVERHEAD_SIZE;
            hexDump(pCh + LEAD_OVERHEAD_SIZE, iBytesToSend, iBytesPerLine);
        }
        else if (pAllocNode->cAF == 'F')
        {  // It is a Free Item
            pFreeNode = (FreeNode *)pCh;
            printf("\t%08lX %-5s %4d", ULAddr(pFreeNode), "Free", iTempSize);
            if (pEnd < pMgr->pBeginStorage
                || pEnd > pMgr->pEndStorage)
                printf(" Bad Item Size");
            else
            {
                short shEndSize = *((short *)(pEnd - sizeof(short)));
                printf(" End Size=%4d", shEndSize);
            }
            printf("\n");
            printf("\t\t\t   Prev=%08lX,Next=%08lX\n"
                , ULAddr(pFreeNode->pPrev)
                , ULAddr(pFreeNode->pNext));

        }
        else
        {
            printf("\t%08lX %-5s %4d"
                , ULAddr(pAllocNode), "Unkn", iTempSize);
        }
    }
}
/*
** This Hex Dump can be used instead of calling the real
** hexDump from smPrintAll if using Visual Studion.  Rename this to hexDump.
** Please remember to remove it when you run your code on a fox server.
** Note: this can't be used in place of calling hexDump for the DUMP command.
*/
int dumbHexDump(char *sbBuffer, int iBufferLength, int iBytesPerLine)
{
    printf("\t\t\t, %s", sbBuffer);  // print the data
    return 1;   // arbitrary value and meaningless in this case
}

/******************** getSimpleToken **************************************
 int getSimpleToken(char szInput[], int *piBufferPosition, char szToken[])
 Purpose:
    Returns the next token in a string.  The delimiter for the token is a 
    space, a newline, carriage return or the end of the string.  To help 
    with a subsequent call, it also returns the next position in the buffer.
Parameters:
    I   char szInput[]          input buffer to be parsed
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
    - If the token is larger than the szToken parm, we return a truncated value.
**************************************************************************/

int getSimpleToken(char szInput[], int *piBufferPosition, char szToken[]) 
{
    int iDelimPos;                      // found position of delim
    int iCopy;                          // number of characters to copy
    char szDelims[20] = " \n\r";        // delimiters
    
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


