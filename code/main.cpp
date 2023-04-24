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

    printf ("SUCCESS - reading %u words\n", text->size);
    assert (("ERROR - null ptr to text structure!\n", text));
    
    //draw_compare_graph (text);
    search_all (text);

    free (text->buffer);
    free (text);
    free (buffer);

    return 0;
}

//-----------------------------------------------------------------------------