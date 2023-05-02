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

void hashTableDump (Hash_table *hash_table)
{
    printf ("___________________________ HASH TABLE ___________________________\n\n"
            "SIZE: %u\n\n", hash_table->size                                         );

    for(unsigned int i = 0; i < hash_table->size; i++)
    {
        printf ("(bucket %d, size %u): ", i, findListSize (&hash_table->bucket[i]));

        Node *curr_node = hash_table->bucket[i].head;
        
        while(curr_node)
        {
            printf ("%s, ", curr_node->line);
            curr_node = curr_node->next;
        }

        printf ("\n");
    }

    printf ("__________________________________________________________________\n\n");
}

//-----------------------------------------------------------------------------

void insertNode (char *line, Hash_table *hash_table, unsigned int hash_val)
{
    Node *new_node = (Node*) calloc (1, sizeof (Node));
    new_node->line = line;
    pushHead (new_node, &hash_table->bucket[hash_val]);
}

//-----------------------------------------------------------------------------

Node *searchLine (char *line,     
                  Hash_table *hash_table, 
                  unsigned int hash_val, 
                  int (*comp_funct)(const char *s1, const char *s2),
                  int *total)
{
    Node *curr_node = hash_table->bucket[hash_val].head;

    while(curr_node)
    {       //strCmpAVX //strncmp

        (*total)++;

        if(!comp_funct (curr_node->line, line))
        {
            //printf ("%d,", *total);
            return curr_node;
        }

        curr_node = curr_node->next;
    }

    return NULL;
}

//-----------------------------------------------------------------------------

int strcmpAvx (const char *s1, const char *s2)
{
    __m256i *s1_vector = ( __m256i* ) s1;
    __m256i *s2_vector = ( __m256i* ) s2;

    __m256i cmp = _mm256_cmpeq_epi8 (*s1_vector, *s2_vector);
    int cmp_mask = _mm256_movemask_epi8 (cmp);

    if(cmp_mask == equal_mask) 
    {
        return 0;
    }

    return 1;
}

//-----------------------------------------------------------------------------

void searchingAll (Text *text, int (*comp_funct)(const char *s1, const char *s2))
{
    Hash_table hash_table = { 0 };
    hashTableCtor (&hash_table, hash_size);
                                                        //superSecretHf _trollohash //Crc32hf
    fillHashTable (text->buffer, text->size, &hash_table, superSecretHf, comp_funct);

    //hashTableDump (hash_table);

    int total = 0;

    for(int i = 0; i < hash_table.size; i++)
    {
        Node *curr_node = hash_table.bucket[i].head;

        while(curr_node)
        {
            for(int j = 0; j < num_of_searchs; j++) //Now search it three hundred times
            {                       //superSecretHf _trollohash //Crc32hf
                unsigned hash_val = superSecretHf (curr_node->line) % hash_size; //Calculate key of current line in hash table
                
                Node *node = searchLine (curr_node->line, &hash_table, hash_val, comp_funct, &total);

                if(!node) //Also we need to avoid O2 roma stunts (цыганские фокусы)
                {
                    printf ("\n\n\nERROR - missed node!\n\n\n");
                }
            }

            curr_node = curr_node->next;
        }
    }

    printf ("TOTAL COMPARISONS - ||%d||\n\n", total);

    hashTableDtor (&hash_table); 
}

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
        //roundLeftHf,
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

    fillHashTable (text->buffer, text->size, &hash_table, calc_hash, strcmp);
    fillInDataGraph (&hash_table, graph);

    hashTableDtor (&hash_table);
}

//-----------------------------------------------------------------------------

void fillInDataGraph (Hash_table *hash_table, FILE *graph)   
{
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
        fprintf (graph, "%u", findListSize (&hash_table->bucket[i]));

        if(i != hash_size - 1)
        {
            fprintf (graph, ", ");
        }
    }

    fprintf (graph, "])\n");
}

//-----------------------------------------------------------------------------

void fillHashTable (char **buffer, 
                    unsigned int size,
                    Hash_table *hash_table, 
                    uint32_t (*calc_hash)(char *line),
                    int (*comp_funct)(const char *s1, const char *s2))
{

    int total = 0;

    for(unsigned int i = 0; i < size; i++)
    {
        unsigned hash_val = calc_hash (buffer[i]) % hash_size;

        if(searchLine (buffer[i], hash_table, hash_val, comp_funct, &total))
        {
            continue;
        }

        insertNode (buffer[i], hash_table, hash_val);
    }
}

//-----------------------------------------------------------------------------

unsigned int calculateStdDeviation (Hash_table *hash_table)
{
    unsigned int average_value = calculateAverageValue (hash_table);
    unsigned int tmp_value     = 0;
    
    for(unsigned int i = 0; i < hash_table->size; i++)
    {
        tmp_value += pow (findListSize (&hash_table->bucket[i]) - average_value, 2);
    } 

    tmp_value /= hash_table->size;

    return (sqrt (tmp_value));
}

//-----------------------------------------------------------------------------

unsigned int calculateAverageValue (Hash_table *hash_table)
{
    unsigned int tmp_value = 0;
    
    for(unsigned int i = 0; i < hash_table->size; i++)
    {
        tmp_value += findListSize (&hash_table->bucket[i]);
    } 

    return (tmp_value /= hash_table->size);
}

//-----------------------------------------------------------------------------
