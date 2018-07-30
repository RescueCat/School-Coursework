/**********************************************************************
cs3743p1.c by Jonathan Houston
Purpose:	
    A program that handles reading and writting to a hashed file.
Command Parameters:
    Commands parameters are detailed and outlined in cs3743p1Driver.c 
Input:
    Commands from cs3743p1Driver.c 
Results:
    Creation of a hash file that can be written and read from.
Returns:
    RC_OK                   When the record location is found
    RC_LOC_NOT_FOUND        When the record location is not found
    RC_SYNONYM              If the RBN is already associated
    RC_REC_NOT_FOUND        When the record is not found
    RC_FILE_EXISTS          If the file already exists
    0                       Upon success
    fileRead                The open file pointer
    NULL                    If the file doesn't exists
    NULL                    If the read fails
Notes:
    More about return values can be found in cs3743p1Driver.c
**********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

/**********************************************************************
cs3743p1.h
Purpose:
	include file which contains constants, HashHeader and Book 
	typedefs, and function prototypes.
Notes:

**********************************************************************/
#include "cs3743p1.h"


/******************** hashCreate********************************************
int hashCreate(char szFileNm[], HashHeader *pHashHeader)
Purpose:
	This function creates a hash file containing only the HashHeader record.
Parameters:
	I char szFileNm[]		Name of the file to be created
	I HashHeader *pHashHeader	Header record to be written to file
Notes:

Return Values:
	RC_FILE_EXISTS			If the file already exists
	0				Upon success
********************************************************G**************/
int hashCreate(char szFileNm[], HashHeader *pHashHeader)
{
        FILE *writeFile; 	//Write File (stream)
	int jCount; 		//Integer to test successful writes

        // If the file already exists, return RC_FILE_EXISTS
        if (writeFile = fopen(szFileNm, "rb+"))
        {
                fclose(writeFile);
                return RC_FILE_EXISTS;
        }
        else
        {
		//Create the binary file by opening it.
                writeFile = fopen(szFileNm, "wb+");
                if(writeFile == NULL)
                        printf("hashCreate File write fail \n");
        }

        //Set pHashHeader->iHighOverflowRBN to the value of pHashHeader->iNumPrimary
        pHashHeader -> iHighOverflowRBN = pHashHeader ->iNumPrimary;

	//Write the HashHeader record to the file at RBN 0.
        //pHashHeader -> iRecSize = sizeof(Book);
        jCount = fwrite(pHashHeader, pHashHeader -> iRecSize, 1L, writeFile);
        if(jCount != 1)
                /*printf("Write fail\n");*/

	//fclose the file.
        fclose(writeFile);
        return 0;
}

/******************** hashOpen********************************************
FILE *hashOpen(char szFileNm[], HashHeader *pHashHeader)
Purpose:
	This function opens an existing hash file which must 
	contain a HashHeader record and returns a file pointer to it.
Parameters:
	I char szFileNm[]               Name of the file to be created
        I HashHeader *pHashHeader       Header record to be written to file
Notes:
	This function has TWO instances where it will return NULL.
Return Values:
	fileRead			The open file pointer
	NULL				If the file doesn't exists
	NULL				If the read fails
**********************************************************************/
FILE *hashOpen(char szFileNm[], HashHeader *pHashHeader)
{

        FILE *fileRead; 	//Read File (stream)
	int jCount;		//Integer to test successful reads

        //Use fopen to open the file.        
        if (fileRead = fopen(szFileNm, "rb+"))
        {
                //Use fread to read the HashHeader record and return it through the parameter
                jCount = fread(pHashHeader, pHashHeader -> iRecSize, 1L, fileRead);
                //If the read fails, return NULL.
		if(jCount != 1)
                {
                        /*printf("Hash Open Read Fail\n");*/
                        return NULL;
                }
		//Return the opened FILE pointer as the function value when successful.
                return fileRead;
        }
	//If it doesn't exist, return NULL.
        else
        {
                return NULL;
        }
}

/******************** readRec********************************************
int readRec(FILE *pFile, int iRBN, void *pRecord, int iRecSize)
Purpose:
	This function reads a record of the specified size at 
	the specified RBN in the specified file.
Parameters:
	I FILE *pFile 		The file pointer to be read from
	I int iRBN		The record book number of the book to be read
	I void *pRecord		The book record to be read
	I int iRecSize		The size of each record
Notes:

Return Values
	RC_LOC_NOT_FOUND	When the record location is not found
	RC_OK			When the record location is found
**********************************************************************/
int readRec(FILE *pFile, int iRBN, void *pRecord, int iRecSize)
{       
	int RBA; 		//Integer that holds the start of the Record Book Area of the file
	int jCount;		//Integer to test successful reads

        //Determine the RBA based on iRBN and iRecSize.
        RBA = iRBN * iRecSize;
        
	//Use fseek to position the file in that location.
        fseek(pFile, RBA, SEEK_SET);

	//Use fread to read that record and return it through pRecord.
        jCount = fread(pRecord, iRecSize, 1L, pFile);
	if(jCount == 0)
        {
        	/*printf("readRec Read Fail\n");*/
       	}

        //If the location is not found, return RC_LOC_NOT_FOUND.
	if(pRecord == NULL)
                return RC_LOC_NOT_FOUND;
	//Otherwise, return RC_OK.
        else
                return RC_OK;        
}

/******************** writeRec********************************************
int writeRec(FILE *pFile, int iRBN, void *pRecord, int iRecSize)
Purpose:
        This function writes a record of the specified size at the 
	specified RBN in the specified file. 
Parameters:
        I FILE *pFile           The file pointer to be read from
        I int iRBN              The record book number of the book to be written
        I void *pRecord         The book record to be written
        I int iRecSize          The size of each record
Notes:

Return Values
        RC_LOC_NOT_FOUND        When the record location is not found
        RC_OK                   When the record location is found
**********************************************************************/
int writeRec(FILE *pFile, int iRBN, void *pRecord, int iRecSize)
{
	int RBA;                //Integer that holds the start of the Record Book Area of the file
        int jCount;             //Integer to test successful writes	

	//Determine the RBA based on iRBN and iRecSize
        RBA = iRBN * iRecSize;
        
	//Use fseek to position the file in that location.
        fseek(pFile, RBA, SEEK_SET);

	//Use fwrite to write that record to the file.
        jCount = fwrite(pRecord, iRecSize, 1L, pFile);
	
	//If the fwrite fails, return RC_LOC_NOT_WRITTEN
	if(jCount == 0)
        {
        	return RC_LOC_NOT_WRITTEN;
        }
	//Otherwise, return RC_OK.
	else
		return RC_OK;

}

/******************** bookInsert*******************************************
int bookInsert(FILE *pFile, HashHeader *pHashHeader, Book *pBook)
Purpose:
       	This function inserts a book into the specified file.
Parameters:
        I FILE *pFile           	The file pointer to be read/written from
	I HashHeader *pHashHeader       Header record of the file
        I Book *pBook			The book to be written to the file
Notes:

Return Values
        RC_FILE_EXISTS                  If the file already exists
        RC_SYNONYM                   	If the RBN is already associated
**********************************************************************/
int bookInsert(FILE *pFile, HashHeader *pHashHeader, Book *pBook)
{
	int RBN;                //Integer that holds the Record Book Number in the file
        Book testBook;          //Book structure used for comparison
	
	//Determine RBN using hash function
	RBN = hash(pBook -> szBookId, pHashHeader);
	
	//Use readRec to read the record at that RBN.  
        readRec(pFile, RBN, &testBook, pHashHeader -> iRecSize);

	//If that location doesn't exist or the record at that location has a szBookId[0] == '\0':
	if((testBook.szBookId == NULL) || (testBook.szBookId[0] == '\0'))
        {
                //Set iNextChain to 0
        	pBook -> iNextChain = 0;
	
		//Write the record to the file
        	writeRec(pFile, RBN, pBook, pHashHeader -> iRecSize);
        }
        //If that record exists
	else
	{
		// and that book's szBookId matches
		if(strcmp(testBook.szBookId, pBook -> szBookId)== 0)
		{
			return RC_REC_EXISTS; //Do not update
		}
		else
		{
			return RC_SYNONYM;
		}
	}
}

/******************** bookRead*******************************************
int bookRead(FILE *pFile, HashHeader *pHashHeader, Book *pBook)
Purpose:
        This function reads the specified book by its szBookId.
Parameters:
        I FILE *pFile                   The file pointer to be read from
        I HashHeader *pHashHeader       Header record of the file
        I Book *pBook                   The book record to be read from the file
Notes:

Return Values
        RC_REC_NOT_FOUND        When the record is not found
        RC_OK                   When the record location is found
**********************************************************************/
int bookRead(FILE *pFile, HashHeader *pHashHeader, Book *pBook)
{
	int RBN;                //Integer that holds the Record Book Number in the file
	Book testBook; 		//Book structure used for comparison
	
	//Determine RBN using hash function
      	RBN = hash(pBook -> szBookId, pHashHeader);

	//Use readRec to read the record at that RBN. 
	readRec(pFile, RBN, &testBook, pHashHeader -> iRecSize);
	/*printf("Test book ID: %s pbook ID: %s \n", testBook.szBookId, pBook -> szBookId); */
	
	//If the book at that location matches the specified szBookId, return the book via pBook and return RC_OK.
	if(strcmp(testBook.szBookId, pBook -> szBookId)== 0)
	{
		readRec(pFile, RBN, pBook, pHashHeader -> iRecSize);
		return RC_OK;
	}
	//Otherwise, return RC_REC_NOT_FOUND 
	else
	{
		return RC_REC_NOT_FOUND;
	}
}
