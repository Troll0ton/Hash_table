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

//void list_ctor (List *list);
void list_dtor (List *list);
unsigned int find_list_size (List *list);

void hash_table_ctor (Hash_table *hash_table, uint32_t size);
void hash_table_dtor (Hash_table *hash_table);

void push_head (char *line, List *list);

void insert_node (char *line, Hash_table hash_table, uint32_t (*calc_hash)(char *line));
Node *search_line (char *line, Hash_table hash_table, uint32_t (*calc_hash)(char *line));

void draw_graph (void (*funct) (const char *str, ...), FILE *file, char *main_line);
void hash_table_dump (Hash_table hash_table);

//-----------------------------------------------------------------------------

#endif //HASH_TABLE_H