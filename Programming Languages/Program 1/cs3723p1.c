/**********************************************************************
cs3723p1.c by Jonathan Houston
Purpose:
    This program (1)intializes a heap of memory passed by the driver program,
    (2)Allocated nodes inside of the memory with data, and (3)removes specified 
    nodes from the memory and joines them to the begining. 	  
Command Parameters:
    Are detailed and outlined in cs3743p1Driver.c
Results:
    Initializes a heap of memory that can be written to, and rearranged.
Returns:
   pAllocNode			An allocated node in the heap
   NULL				If the node cannot be allocated
   0 				Upon Success 
   pFreeNode->shItemSize	To keep track of Freed node size
   pFreeNode			Upon success of finding an open node
Notes:
	This program is incomplete and is a submission for partial credit.
**********************************************************************/
#include <string.h>

/**********************************************************************
cs3723p1.h
Purpose:
	include file wich contains contsnts, typedefs, and function
	prototypes.
Notes:

**********************************************************************/
#include "cs3723p1.h"


int combineNodes(StorageManager *pMgr, FreeNode *pFreeNode, SMResult *psmResult);
FreeNode * findNode(StorageManager *pMgr, short shSize, SMResult *psmResult);
FreeNode * removeNode(FreeNode * pFreeNode);

/************************ smInit **************************************
void smInit(StorageManager *pMgr)
Purpose:
	To intialize a heap of memeory to all zeroes, set up the heap 
	as one, big, free node, and and set the size
Parameters:
	I void smInit(StorageManager *pMgr)	Void point to StorageManager Struct
Notes:
	This does not have any return values
Return Values:

**********************************************************************/
void smInit(StorageManager *pMgr)
{
	/*Assume the driver has actually allocated the memory for the heap and set 			
	StorageManager's pBeginStorage to point to it.  The driver also sets the 			
	StorageManager's shHeapSize and shMinimumSize.*/

	//Clear out the entire heap with 0 values. 
	memset(pMgr->pBeginStorage, 0, pMgr->shHeapSize);

	//Set up the entire heap as one free node (with appropriate size) and 
	//set the StorageManager's pFreeList to point to it.
	pMgr->pFreeList = (FreeNode *) pMgr->pBeginStorage;

	//The end of that free node must also have its size.
	pMgr->pFreeList->shItemSize = pMgr->shHeapSize;
	pMgr->pEndStorage = pMgr->pBeginStorage + pMgr->shHeapSize;
	
}

/************************ smAlloc  **************************************
void * smAlloc(StorageManager *pMgr, short shDataSize, char sbData[], SMResult *psmResult)
Purpose:
        To create and allocate a node inside the free heap memory space
Parameters:
        I StorageManager *pMgr     	Void point to StorageManager Struct
	I short shDataSize		Size of the data to be written
	I char sbData[]			The actual data to be written
	I SMResult *psmResult		The result of the allocation
Notes:
        
Return Values:
	pAllocNode			Upon success
	NULL				Upon failure
**********************************************************************/
void * smAlloc(StorageManager *pMgr, short shDataSize, char sbData[], SMResult *psmResult)
{
	FreeNode *pFreeNode = NULL;					//Container for the node we need to make
	AllocNode *pAllocNode = NULL;                			//Actual node we are allocating

	//Search for a free node with enough memory to satisfy the needed size
	pFreeNode = findNode(pMgr, (shDataSize + OVERHEAD_SIZE), psmResult);
	if(pFreeNode != NULL) 
   	{
		pAllocNode = (AllocNode *) pFreeNode;                
		//Set the size
      		pAllocNode->shItemSize = pFreeNode->shItemSize; 
		//Set the use flag 
		pAllocNode -> cAF = 'A';     
		//Copy the data
      		strcpy(pAllocNode->sbAllocDumb, sbData);
      		// Move pointer to data
      		pAllocNode = (AllocNode *)((char *)pAllocNode + OVERHEAD_SIZE);
      		psmResult->rc = 0;
		return pAllocNode;
   	}
	psmResult->rc = 1;
	strcpy(psmResult->szErrorMessage, "Cannot allocate.\n");
	return NULL;	
}

/************************ smFree **************************************
short smFree(StorageManager *pMgr, char *pUserData, SMResult *psmResult)
Purpose:
        To free an allocated node inside the free heap memory space and
	join it to the front.
Parameters:
        I StorageManager *pMgr          Void point to StorageManager Struct
        I short pUserData               Information about the node 
        I SMResult *psmResult           The result of the allocation
Notes:
        
Return Values:
     	iTotalSize			If successful, the size of the free node
	0				Upon failure
**********************************************************************/
short smFree(StorageManager *pMgr, char *pUserData, SMResult *psmResult)
{
	
	int iTotalSizeFreed = 0;					//To keep count of the size of the empty node
   	FreeNode *pFreeNode = (FreeNode *)((char *)pUserData);		//Container to the node needing to be freed
   	
	//Check if the node is allocated
	if(pFreeNode->cAF = 'A') 
   	{	
      		iTotalSizeFreed = combineNodes(pMgr, pFreeNode, psmResult);
      		return iTotalSizeFreed;
   	}
   	
	//If the node is already freed
	psmResult->rc = SMERR_CANT_FREE; 
   	strcpy(psmResult->szErrorMessage, "Not an allocated node.\n");
   	return 0;
}

/************************ combineNodes **************************************
int combineNodes(StorageManager *pMgr, FreeNode *pFreeNode, SMResult *psmResult)
Purpose:
        To to combine nodes together to the front of the the heap. 
Parameters:
        I StorageManager *pMgr          Void point to StorageManager Struct
        I short pFreeNode               The node to combine to the front 
        I SMResult *psmResult           The result of merge
Notes:
        
Return Values:
        pFreeNode->shItemSize		The size of the node merged
**********************************************************************/
int combineNodes(StorageManager *pMgr, FreeNode *pFreeNode, SMResult *psmResult)
{  
	// Remove the node from the list
   	pFreeNode = removeNode(pFreeNode); 

   	// Hook into front of list, configure as front node
   	pMgr->pFreeList->pPrev = pFreeNode;
   	pFreeNode->pNext = pMgr->pFreeList;
   	pMgr->pFreeList = pFreeNode;
   	pFreeNode->pPrev = NULL;

   	return pFreeNode->shItemSize;
}

/************************ findNodes **************************************
FreeNode * findNode(StorageManager *pMgr, short shSize, SMResult *psmResult)
Purpose:
        To find the next free node that is big enough to store the information
	to be coppied.
Parameters:
        I StorageManager *pMgr          Void point to StorageManager Struct
        I short iSize	               	The minimu sized node to find  
        I SMResult *psmResult           The result of the search
Notes:
        
Return Values:
        pFreeNode			Upon success, a proper
	NULL				Upon failure
**********************************************************************/
FreeNode * findNode(StorageManager *pMgr, short shSize, SMResult *psmResult)
{
	FreeNode * pFreeNode = NULL;				//Container used to find a node
 	short iActualSize;					//the actual size of the node
	

	for (pFreeNode = pMgr->pFreeList; pFreeNode != NULL; pFreeNode = pFreeNode->pNext)
   	{
		if(pFreeNode->shItemSize >= shSize)
      		{
			if((pFreeNode->shItemSize - shSize) > pMgr->shMinimumSize)
         		{
				iActualSize = shSize;
				FreeNode *pNewFreeNode = NULL;
			
				if(iActualSize < pMgr-> shMinimumSize)
				{
					iActualSize = pMgr->shMinimumSize;
				}
			
				// set up the new FreeNode to be inserted into FreeList
            			// set address for new FreeNode that takes up remaining space
            			pNewFreeNode = (FreeNode *)((char *)pFreeNode + iActualSize);
            
				// configure new node with previous nodes pointers to keep list
            			pNewFreeNode->pNext = pFreeNode->pNext;
            			pNewFreeNode->pPrev = pFreeNode->pPrev;
            
				// set the new size
            			pNewFreeNode->shItemSize = pFreeNode->shItemSize - iActualSize;

	            		// set new size for the returned FreeNode
        	    		pFreeNode->shItemSize = iActualSize;
	
				// link NewFreeNode into the list
            			if(pNewFreeNode->pPrev != NULL)
            			{
               				pNewFreeNode->pPrev->pNext = pNewFreeNode;
            			}
            			if(pNewFreeNode->pNext != NULL)
            			{
               				pNewFreeNode->pNext->pPrev = pNewFreeNode;
            			}
            
            			// if selected FreeNode began FreeList, configure properly
            			if(pFreeNode == pMgr->pFreeList)
            			{
               				pMgr->pFreeList = pNewFreeNode;
            			}	
			}
			else
			{
				pFreeNode = removeNode(pFreeNode);
			}
			return pFreeNode;
		} 
	}
	psmResult->rc = SMERR_NOT_AVAIL;
	strcpy(psmResult->szErrorMessage, "Could not find a node large enough.\n");
   	return NULL;	
}

/************************ removeNode **************************************
FreeNode * removeNode(FreeNode * pFreeNode)
Purpose:
        To remove an allocated node from the heap and and link it's 
	previous and next  nodes together.
Parameters:
        I pFreeNode			The node that needs to be removed
Notes:
        
Return Values:
        pFreeNode                       Upon success the node that has been removed
**********************************************************************/
FreeNode * removeNode(FreeNode * pFreeNode)
{
	if(pFreeNode->pPrev != NULL)
   	{
      		pFreeNode->pPrev->pNext = pFreeNode->pNext;      
   	}
   	if(pFreeNode->pNext != NULL)
   	{
      		pFreeNode->pNext->pPrev = pFreeNode->pPrev;
   	}
   	return pFreeNode;
}
