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

    draw_compare_graph (text);

    free (text->buffer);
    free (text);
    free (buffer);

    return 0;
}

//-----------------------------------------------------------------------------