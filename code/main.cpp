#include "../include/hash_table.h"
#include "../include/input_utils.h"
#include "../include/hash_functions.h"

//-----------------------------------------------------------------------------

int main()
{
    FILE *file = fopen ("text.txt", "r+");
    char *buffer = file_reader (file);
    fclose (file);

    Text *text = buffer_separator (buffer);

    /*
    for(unsigned int i = 0; i < text->size; i++)
    {
        printf ("%s\n", text->buffer[i]);
    }
    */

    Hash_table hash_table = { 0 };
    hash_table_ctor (&hash_table, HASH_SIZE);

    for(unsigned int i = 0; i < text->size; i++)
    {
        insert_node (text->buffer[i], hash_table, &super_secret_hf);
    }

    //hash_table_dump (hash_table);

    //Node *curr_node = search_line (line, hash_table, &const_hf);
    
    hash_table_dtor (&hash_table);

    free (text->buffer);
    free (text);
    free (buffer);

    return 0;
}

//-----------------------------------------------------------------------------