#include "../include/input_utils.h"
#include "../include/text_utils.h"

//-----------------------------------------------------------------------------

char *fileReader (FILE *file)
{
    unsigned int file_size = findFileSize (file);

    fseek (file, 0, SEEK_SET);
    char *buffer = (char*) calloc (file_size + 1, sizeof (char));
    fread (buffer, sizeof (char), file_size, file);

    return buffer;
}

//-----------------------------------------------------------------------------

unsigned int findFileSize (FILE *file)
{
    unsigned int file_size = 0;

    while (fgetc (file) != EOF)
    {
        file_size++;
    }

    return file_size;
}

//-----------------------------------------------------------------------------
