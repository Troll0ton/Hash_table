#include "../include/input_utils.h"

//-----------------------------------------------------------------------------

char *file_reader (FILE *file)
{
    unsigned int file_size = find_file_size (file);

    fseek (file, 0, SEEK_SET);

    char *buffer = (char*) calloc (file_size + 1, sizeof (char));

    fread (buffer, sizeof (char), file_size, file);

    return buffer;
}

//-----------------------------------------------------------------------------

unsigned int find_file_size (FILE *file)
{
    unsigned int file_size = 0;

    while (fgetc (file) != EOF)
    {
        file_size++;
    }

    return file_size;
}

//-----------------------------------------------------------------------------

unsigned int find_num_of_words (char *buffer)
{
    unsigned int num_of_words = 0;
    unsigned int i = 0;

    while(buffer[i] != 0)
    {
        if(buffer[i] == '\n' || buffer[i] == ' ')
        {
            num_of_words++;
        }

        i++;
    }

    return num_of_words;
}

//-----------------------------------------------------------------------------

Text *buffer_separator (char *buffer)
{
    Text *text = (Text*) calloc (1, sizeof (Text));

    text->size = find_num_of_words (buffer);
    text->buffer = (char**) calloc (text->size, sizeof (char*));

    unsigned int i = 0;
    unsigned int curr_size = 0;
    char *curr_word = buffer;

    while(buffer[i] != 0)
    {
        if(buffer[i] == '\n' || buffer[i] == ' ')
        {
            buffer[i] = '\0';
            text->buffer[curr_size++] = curr_word;
            curr_word = buffer + i + 1;
        }

        i++;
    }

    return text;
}

//-----------------------------------------------------------------------------