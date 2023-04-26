#include "../include/hash_table.h"

//-----------------------------------------------------------------------------

void listDtor (List *list)
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

unsigned int findListSize (List *list)
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

void hashTableCtor (Hash_table *hash_table, uint32_t size)
{
    hash_table->bucket = (List*) calloc (size, sizeof (List));
    hash_table->size   = size;
}

//-----------------------------------------------------------------------------

void hashTableDtor (Hash_table *hash_table)
{
    for(unsigned int i = 0; i < hash_table->size; i++)
    {
        listDtor (&hash_table->bucket[i]);
    }

    free (hash_table->bucket);

    hash_table->size = deleted_par;
}

//-----------------------------------------------------------------------------

void pushHead (Node *new_node, List *list)
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

void insertNode (char *line, Hash_table hash_table, unsigned int hash_val)
{
    if(searchLine (line, hash_table, hash_val))
    {
        return;
    }

    Node *new_node = (Node*) calloc (1, sizeof (Node));
    new_node->line = line;
    pushHead (new_node, &hash_table.bucket[hash_val]);
}

//-----------------------------------------------------------------------------

Node *searchLine (char *line, Hash_table hash_table, unsigned int hash_val)
{
    Node *curr_node = hash_table.bucket[hash_val].head;

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

Node *searchLine256Bit (__m256i *line, Hash_table hash_table, unsigned int hash_val)
{
    Node *curr_node = hash_table.bucket[hash_val].head;

    while(curr_node)
    {
        if(!strCmpAVX (*((__m256i*)(curr_node->line)), *line))
        {
            return curr_node;
        }

        curr_node = curr_node->next;
    }

    return NULL;
}

//-----------------------------------------------------------------------------

inline size_t strCmpAVX (__m256i str_1, __m256i str_2)
{
    __m256i cmp = _mm256_cmpeq_epi8 (str_1, str_2);
    int mask = _mm256_movemask_epi8 (cmp);

    if(mask == 0xffffffff) 
    {
        return 0;
    }

    return 1;
}

//-----------------------------------------------------------------------------

void hashTableDump (Hash_table hash_table)
{
    printf ("___________________________ HASH TABLE ___________________________\n\n"
            "SIZE: %u\n\n", hash_table.size                                         );

    for(unsigned int i = 0; i < hash_table.size; i++)
    {
        printf ("(bucket %d): %u\n", i, findListSize (&hash_table.bucket[i]));
    }

   printf ("__________________________________________________________________\n\n");
}

//-----------------------------------------------------------------------------

void searchingAll256 (Text_256 *text_256)
{
    Hash_table hash_table = { 0 };
    hashTableCtor (&hash_table, hash_size);

    for(unsigned int i = 0; i < text_256->size; i++)
    {
        unsigned hash_val = superSecretHf256Bit (&text_256->buffer[i]);
        insertNode ((char*)(&text_256->buffer[i]), hash_table, hash_val);
    }

    for(int i = 0; i < num_of_searchs; i++)
    {
        for(int j = 0; j < text_256->size; j++)
        {
            unsigned hash_val = superSecretHf256Bit (&text_256->buffer[i]);
            searchLine256Bit (&text_256->buffer[i], hash_table, hash_val);
        }
    }

    hashTableDtor (&hash_table);
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

void compareHashFunctions (Text *text)
{
    uint32_t (*hf[])(char *line) =
    {
        //constHf,
        //firstSymHf,
        //lenHf,
        //sumHf,
        //roundRightHf,
        roundLeftHf,
        superSecretHf,
    };

    FILE *graph = fopen ("graph.py", "w+");

    fprintf (graph, "import matplotlib as mpl\n"
                    "import matplotlib.pyplot as plt\n"
                    "import numpy as np\n\n"
                    "plt.axis ([0, %u, 0, %u])\n\n",
                    hash_size, y_len);
                    //x_len

    for(int i = 0; i < num_of_hf; i++)
    {
        drawOneFunctionGraph (text, hf[i], graph);
    }

    fprintf (graph, "plt.show()\n");

    fclose (graph);
}

//-----------------------------------------------------------------------------

void drawOneFunctionGraph (Text *text, uint32_t (*calc_hash)(char *line), FILE *graph)
{
    Hash_table hash_table = { 0 };
    hashTableCtor (&hash_table, hash_size);

    for(unsigned int i = 0; i < text->size; i++)
    {
        unsigned hash_val = calc_hash (text->buffer[i]);
        insertNode (text->buffer[i], hash_table, hash_val);
    }

    fprintf (graph, "plt.bar ([");

    for(int i = 0; i < hash_size; i++)
    {
        fprintf (graph, "%d", i);

        if(i != hash_size - 1)
        {
            fprintf (graph, ", ");
        }
    }

    fprintf (graph, "], [");

    for(int i = 0; i < hash_size; i++)
    {
        fprintf (graph, "%u", findListSize (&hash_table.bucket[i]));

        if(i != hash_size - 1)
        {
            fprintf (graph, ", ");
        }
    }

    fprintf (graph, "])\n");

    hashTableDtor (&hash_table);
}

//-----------------------------------------------------------------------------
