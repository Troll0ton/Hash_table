#include "../include/hash_table.h"

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
    uint32_t i = calc_hash (line);

    Node *new_node = (Node*) calloc (1, sizeof (Node));
    new_node->line = line;
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

   printf ("__________________________________________________________________\n\n");
}

//-----------------------------------------------------------------------------

void draw_compare_graph (Text *text)
{
    uint32_t (*hf[])(char *line) =
    {
        const_hf,
        first_sym_hf,
        len_hf,
        sum_hf,
        round_right_hf,
        round_left_hf,
        super_secret_hf
    };

    FILE *graph = fopen ("graph.py", "w+");

    fprintf (graph, "import matplotlib as mpl\n"
                    "import matplotlib.pyplot as plt\n"
                    "import numpy as np\n\n"
                    "plt.axis ([0, %u, 0, 10])\n\n",
                    HASH_SIZE);

    for(int i = 0; i < NUM_OF_HF; i++)
    {
        draw_one_function (text, hf[i], graph);
    }

    fprintf (graph, "plt.show()\n");

    fclose (graph);
}

//-----------------------------------------------------------------------------

void draw_one_function_ (Text *text, uint32_t (*calc_hash)(char *line), FILE *graph, char *hf_name)
{
    Hash_table hash_table = { 0 };
    hash_table_ctor (&hash_table, HASH_SIZE);

    for(unsigned int i = 0; i < text->size; i++)
    {
        insert_node (text->buffer[i], hash_table, calc_hash);
    }

    fprintf (graph, "plt.plot ([");

    for(int i = 0; i < HASH_SIZE; i++)
    {
        fprintf (graph, "%d", i);

        if(i != HASH_SIZE - 1)
        {
            fprintf (graph, ", ");
        }
    }

    fprintf (graph, "], [");

    for(int i = 0; i < HASH_SIZE; i++)
    {
        fprintf (graph, "%u", find_list_size (&hash_table.bucket[i]));

        if(i != HASH_SIZE - 1)
        {
            fprintf (graph, ", ");
        }
    }

    fprintf (graph, "])\n");

    hash_table_dtor (&hash_table);
}

//-----------------------------------------------------------------------------
