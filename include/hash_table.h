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

#define NUM_OF_HF 7

//-----------------------------------------------------------------------------

#define draw_one_function(text, hf_name, graph) draw_one_function_ (text, hf_name, graph, #hf_name)

//-----------------------------------------------------------------------------

void list_dtor (List *list);
unsigned int find_list_size (List *list);

void hash_table_ctor (Hash_table *hash_table, uint32_t size);
void hash_table_dtor (Hash_table *hash_table);

void push_head (char *line, List *list);

void insert_node (char *line, Hash_table hash_table, uint32_t (*calc_hash)(char *line));
Node *search_line (char *line, Hash_table hash_table, uint32_t (*calc_hash)(char *line));

void draw_compare_graph (Text *text);
void draw_one_function_ (Text *text, uint32_t (*calc_hash)(char *line), FILE *graph, char *hf_name);
void hash_table_dump (Hash_table hash_table);

//-----------------------------------------------------------------------------

#endif //HASH_TABLE_H