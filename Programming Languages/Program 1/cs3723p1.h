/**********************************************************************
cs3723p1.h
Purpose:
    Defines constants for
        boolean values
        maximum sizes
        minimum sizes
        program return codes
        error messages
    Defines typedefs for
        FreeNode represents a free item.  FreeNodes appear in a doubly
            linked list.
        AllocNode represents an allocated node.  The actual size of an
            allocated item may be much larger.  The size of an allocated
            item cannot be less than the size of a FreeNode.
        StorageManager is the primary structure used by this program.
        SMResult is used by the smAllocate and smFree functions to
        specify whether they returned values successfully.
    Prototypes
Notes:

**********************************************************************/
#define TRUE 1
#define FALSE 0

#define LEAD_OVERHEAD_SIZE (sizeof(short)+1)              // Does not include trailing size
#define OVERHEAD_SIZE  (LEAD_OVERHEAD_SIZE+sizeof(short)) // All nodes have two shorts and type
#define MAX_KEY_SIZE 10                                   // Maximum size of a key for Hash Table
#define MAX_MESSAGE_SIZE 100                              // Maximum message size for smResult
#define MAX_DATA 200                                      // Max size of sbData
#define MAX_HASH_ENTRIES 100                              // Maximum number of hash entries

#define ERROR_PROCESSING            99                     // error during processing - exit value

// Errors returned in the rc of SMResult
#define SMERR_NOT_AVAIL 901     // There isn't any free memory to handle alloc request
#define SMERR_CANT_FREE 902     // Attempted to free a node which isn't allocated.

// Error messages for unexpected situations in the driver 
#define ERR_NULL_AREA "Storage Mgr Begin is NULL for %s"
#define ERR_ALGORITHM "Unexpected error in algorithm: %s "

// FreeNode represents a free item.  FreeNodes appear in a doubly linked list.
typedef struct FreeNode
{
    short  shItemSize;      // total size of this free item.  
    char   cAF;             // 'A' - allocated, 'F'- free
    struct FreeNode *pPrev; // Pointer to the previous Free Node
    struct FreeNode *pNext; // Pointer to the next Free Node
} FreeNode;

// Note that the end of of the memory for a free item or allocated item
// will contain an additional shItemsize. 

// AllocNode represents an allocated node.  The actual size of an allocated item may be much
// larger.  The size of an allocated item cannot be smaller than a free iten.
typedef struct AllocNode
{
    short shItemSize;                        // total size of the allocated item.  
    char  cAF;                               // 'A' - allocated, 'F'- free
    char  sbAllocDumb[MAX_DATA];             // this is just some dumb data
} AllocNode;

// StorageManager is the primary structure used by this program.  
typedef struct
{
    short shHeapSize;                        // Total size of the heap memory being managed
    short shMinimumSize;                     // Minimum size of a free item
    struct FreeNode *pFreeList;              // Pointer to the free list
    char  *pBeginStorage;                    // Beginning of the heap memory being managed
    char  *pEndStorage;                      // End address immediately after the heap memory
} StorageManager;

// This is returned by smAllocate and smFree via the parmater list.  
typedef struct
{
    int  rc;                                   // Return Code is 0 if it is normal.  Otheriwise,
                                               // it is not zero.  See the defined constants.
    char szErrorMessage[MAX_MESSAGE_SIZE + 1]; // If a problem is encountered, this should 
                                               // explain the error.
} SMResult;

// This is for returning one Hash Table entry pair
typedef struct
{
    char szKey[MAX_KEY_SIZE + 1];              // the hash key
    void *pUserData;                           // the entry contains just a ptr
} HashEntryPair;
// This is used to return the entire contents of the Hash Table
typedef struct
{
    int iNumEntries;
    HashEntryPair entryM[MAX_HASH_ENTRIES];
} HashMO;

// student functions
void * smAlloc(StorageManager *pMgr, short shDataSize, char sbData[]
    , SMResult *psmResult);
short smFree(StorageManager *pMgr, char *pUserData, SMResult *psmResult);
void smInit(StorageManager *pMgr);

// Driver functions
void smPrintFree(StorageManager *pMgr);
void smPrintAll(StorageManager *pMgr);

void errExit(const char szFmt[], ... );

// Hex Dump
int hexDump(char *psbBuffer, int iBufferLength, int iBytesPerLine);
