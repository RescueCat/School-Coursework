/**********************************************************************
hashApi.cpp
Purpose:
    Provides functions for integrating C with c++ Hash Tables 
    (unordered_map).  The hash key is a string and the value is
    a pointer.
Notes:
    extern "C" prototypes are needed for C integration.    
**********************************************************************/
extern "C" {
#include <string.h>
#include "cs3723p1.h"
}

#include <string>
#include <unordered_map>
using namespace std;

// Define the SMHash typedef.  The key is a string and the value
// is a pointer.
typedef std::unordered_map<std::string, void *> SMHash;

// Define a global extern variable for the hash table
SMHash smHashTable;

// "C" prototypes for the hash table functions
extern "C" void *getHash(const char *szKey);
extern "C" void putHash(const char *szKey, void *value);
extern "C" void eraseAll();
//extern "C" void printAll(StorageManager *pMgr);
extern "C" void getAll(HashMO *pHashMO);

/******************** getHash *****************************************
    void * getHash(const char *szKey)
Purpose:
    Uses C++ unordered_map Class to get data from smHashTable.
Parameters:
    i const char *szKey     hash table key value to lookup
Returns:
    pointer representing whatever we need stored in the hash table.
Notes:
    Uses the global smHashTable
**************************************************************************/
void * getHash(const char *szKey)
{
    std::string str = string(szKey);
    return smHashTable[str];
}
/******************** putHash *****************************************
    void putHash(const char *szKey, void *value)
Purpose:
    Uses C++ unordered_map Class to store data in a hash table.
Parameters:
    i const char *szKey     hash table key to lookup
    i void *value           pointer to the value
Notes:
    Uses the global smHashTable 
**************************************************************************/
void putHash(const char *szKey, void *value)
{
    std::string str = string(szKey);
    smHashTable[str] = value;  // Place it in the Hash Table
}
/******************** eraseAll *****************************************
    void eraseAll()
Purpose:
    Erases all entries in the hash table
Parameters:
    n/a
Notes:
    Uses the global smHashTable
**************************************************************************/
void eraseAll()
{
    smHashTable.erase(smHashTable.begin(), smHashTable.end());
}
/******************** getAll *****************************************
    void getAll(void getAll(HashMO *pHashMO)
Purpose:
    Returns an array of Hash Entry Pairs.
Parameters:
    O HASHMO *pHashMO hash message object for returning an array of hash 
                      entry pairs.
Notes:
    - Uses the global smHashTable
    - The array has a max of MAX_HASH_ENTRIES entries
**************************************************************************/
void getAll(HashMO *pHashMO)
{
    int i;
    pHashMO->iNumEntries = 0;
    // Iterate through the entire hash table
    for (auto hashEntry : smHashTable)
    {
        i = pHashMO->iNumEntries;
        pHashMO->entryM[i].pUserData = hashEntry.second;
        if (strlen(hashEntry.first.c_str()) > MAX_KEY_SIZE)
        {  // If the key is too long, truncate it
            strncpy(pHashMO->entryM[i].szKey, hashEntry.first.c_str(), MAX_KEY_SIZE);
            pHashMO->entryM[i].szKey[MAX_KEY_SIZE] = '\0';
        }
        else
            strcpy(pHashMO->entryM[i].szKey, hashEntry.first.c_str());
        pHashMO->iNumEntries += 1;
    }
}