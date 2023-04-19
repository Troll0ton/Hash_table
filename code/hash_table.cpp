#include "../include/hash_table.h"

//-----------------------------------------------------------------------------
/*
void list_ctor (List *list)
{

}
*/
//-----------------------------------------------------------------------------

void list_dtor (List *list)
{
    Node *curr_node = list->head;
    Node *tmp_node = NULL;

    while(curr_node)
    {
        tmp_node = curr_node;
        curr_node = curr_node->next;

        free (tmp_node);
    }
}

//-----------------------------------------------------------------------------

unsigned int find_list_size (List *list)
{
    Node *curr_node = list->head;
    unsigned int curr_len = 0;

    while(curr_node)
    {
        curr_node = curr_node->next;
        curr_len++;
    }

    return curr_len;
}

//-----------------------------------------------------------------------------

void hash_table_ctor (Hash_table *hash_table, uint32_t size)
{
    hash_table->bucket = (List*) calloc (size, sizeof (List));
    hash_table->size   = size;
}

//-----------------------------------------------------------------------------

void hash_table_dtor (Hash_table *hash_table)
{
    for(unsigned int i = 0; i < hash_table->size; i++)
    {
        list_dtor (&hash_table->bucket[i]);
    }

    free (hash_table->bucket);

    hash_table->size = DELETED_PAR;
}

//-----------------------------------------------------------------------------

void push_head (Node *new_node, List *list)
{
    if(!HEAD)
    {
        HEAD = new_node; 
        return;
    }

    Node *tmp_node = HEAD;
    HEAD = new_node;
    HEAD->next = tmp_node;
}

//-----------------------------------------------------------------------------

void insert_node (char *line, Hash_table hash_table, uint32_t (*calc_hash)(char *line))
{
    Node *new_node = (Node*) calloc (1, sizeof (Node));
    new_node->line = line;

    uint32_t i = calc_hash (line);
    push_head (new_node, &hash_table.bucket[i]);
}

//-----------------------------------------------------------------------------

Node *search_line (char *line, Hash_table hash_table, uint32_t (*calc_hash)(char *line))
{
    uint32_t i = calc_hash (line);
    Node *curr_node = hash_table.bucket[i].head;

    while(curr_node)
    {
        if(!strncmp (curr_node->line, line, strlen (line)))
        {
            return curr_node;
        }

        curr_node = curr_node->next;
    }

    return NULL;
}

//-----------------------------------------------------------------------------

void hash_table_dump (Hash_table hash_table)
{
    printf ("___________________________ HASH TABLE ___________________________\n\n"
            "SIZE: %u\n\n", hash_table.size                                         );

    for(unsigned int i = 0; i < hash_table.size; i++)
    {
        printf ("(bucket %d): %u\n", i, find_list_size (&hash_table.bucket[i]));
    }

    /*
    FILE *graph = fopen ("graph.py", "w+");

    fprintf (graph, "import matplotlib as mpl\n"
                    "import matplotlib.pyplot as plt\n"
                    "import numpy as np\n\n"
                    "plt.axis ([0, 1010000, 0, 0.0226])\n\n");

    fprintf (file, "plt.plot ([");

    for(int i = 100000; i < 1000000; i+=100000)
    {
        fprintf (file, "%d, ", i);
    }

    fprintf (file, "], [");

    for(int size = 10; size < 100; size+=10)
    {
        fprintf (file, "%lg, ", time);
    }

    fprintf (file, "])\n\n");

    fclose (graph);
    */

   printf ("__________________________________________________________________\n\n");
}

//-----------------------------------------------------------------------------

void draw_graph (Hash_table *hash_table)
{

}

//-----------------------------------------------------------------------------
