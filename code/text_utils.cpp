#include "../include/text_utils.h"

//-----------------------------------------------------------------------------

unsigned int findNumOfWords (char *buffer)
{
    unsigned int num_of_words = 0;
    unsigned int i = 0;

    while(buffer[i] != '\0')
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

Text *bufferSeparator (char *buffer)
{
    int size = findNumOfWords (buffer);
    Text *text = textCtor (buffer, size);

    unsigned int curr_size = 0;

    char *curr_word = buffer;
    unsigned int str_lenght = strlen (buffer);

    for(unsigned int curr_pos = 0; curr_pos < str_lenght; curr_pos++)
    {
        if((curr_pos - (curr_word - buffer) > 30)               || 
           (buffer[curr_pos] == '\n' || buffer[curr_pos] == ' ')  )
        {
            buffer[curr_pos] = '\0';
            text->buffer[curr_size++] = curr_word;
            curr_word = buffer + curr_pos + 1;
        }
    }

    return text;
}

//-----------------------------------------------------------------------------

char *strTranslator256Bits (Text *text)
{
    char *buffer = (char*) aligned_alloc (32, text->size * 32);
    memset (buffer, 0, text->size * 32);

    for(unsigned int i = 0; i < text->size; i++)
    {
        strncpy (buffer + 32 * i, text->buffer[i], 32); 

        int len = strlen (text->buffer[i]);
    } 

    return buffer;
}

//-----------------------------------------------------------------------------

Text *bufferSeparator256Bit (char *buffer, int size)
{
    Text *text = textCtor (buffer, size);

    for(int i = 0; i < size; i++)
    {
        text->buffer[i] = buffer + 32 * i;
    }

    return text;
}

//-----------------------------------------------------------------------------

Text *textCtor (char *buffer, int size)
{
    Text *text = (Text*) calloc (1, sizeof (Text));

    text->size = size; 
    text->buffer = (char**) calloc (text->size, sizeof (char*));
    
    printf ("SUCCESS - text ctor\n");

    return text;
}

//-----------------------------------------------------------------------------

void textDtor (Text *text)
{
    text->size = deleted_par;
    
    free (text->buffer);
    free (text);

    printf ("SUCCESS - text dtor\n");
}

//-----------------------------------------------------------------------------
