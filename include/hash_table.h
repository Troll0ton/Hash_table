//! @file hash_table.h

#ifndef   HASH_TABLE_H
#define   HASH_TABLE_H

//-----------------------------------------------------------------------------

#include "common.h"
#include "../include/hash_functions.h"

//-----------------------------------------------------------------------------

#define HEAD list->head 

//-----------------------------------------------------------------------------

typedef struct Node
{
   char *line;
   struct Node *next;
} Node;

//-----------------------------------------------------------------------------

typedef struct List
{
    Node *head;
    //uint32_t size;
} List;

//-----------------------------------------------------------------------------

typedef struct Hash_table
{
    List *bucket;
    uint32_t size;
} Hash_table;

//-----------------------------------------------------------------------------

const int num_of_searchs = 500;
const int num_of_hf = 3;
const unsigned int y_len = 20;

//-----------------------------------------------------------------------------

void listDtor (List *list);
unsigned int findListSize (List *list);

void hashTableCtor (Hash_table *hash_table, uint32_t size);
void hashTableDtor (Hash_table *hash_table);

void pushHead (char *line, List *list);
void insertNode (char *line, Hash_table hash_table, unsigned int hash_val);

void searchingAll (Text *text);
Node *searchLine (char *line, Hash_table hash_table, unsigned int hash_val);

void searchingAll256 (Text_256 *text_256);
Node *searchLine256Bit (__m256i *line, Hash_table hash_table, unsigned int hash_val);

inline size_t strCmpAVX (__m256i str_1, __m256i str_2);

void compareHashFunctions (Text *text);
void drawOneFunctionGraph (Text *text, uint32_t (*calc_hash)(char *line), FILE *graph);
void hashTableDump (Hash_table hash_table);

//-----------------------------------------------------------------------------

#endif //HASH_TABLE_H