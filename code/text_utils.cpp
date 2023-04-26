#include "../include/text_utils.h"

//-----------------------------------------------------------------------------

unsigned int findNumOfWords (char *buffer)
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

Text *bufferSeparator (char *buffer)
{
    Text *text = textCtor (buffer);

    unsigned int curr_size = 0;

    char *curr_word = buffer;
    unsigned int str_lenght = strlen (buffer);

    for(unsigned int curr_pos = 0; curr_pos < str_lenght; curr_pos++)
    {
        if(buffer[curr_pos] == '\n' || buffer[curr_pos] == ' ')
        {
            buffer[curr_pos] = '\0';
            text->buffer[curr_size++] = curr_word;
            curr_word = buffer + curr_pos + 1;
        }
    }

    return text;
}

//-----------------------------------------------------------------------------

Text_256 *strTranslator256Bits (Text *text)
{
    Text_256 *text_256 = text256Ctor (text->size);

    //alignas(32) char tmp_str[32] = "";

    for(unsigned int i = 0; i < text->size; i++)
    {
        //strcpy (tmp_str, text->buffer[i]); 

        int len = strlen (text->buffer[i]);

        memcpy (&text_256->buffer[i], text->buffer[i], len);
    } 

    return text_256;
}

//-----------------------------------------------------------------------------

Text *textCtor (char *buffer)
{
    Text *text = (Text*) calloc (1, sizeof (Text));

    text->size = findNumOfWords (buffer);
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

Text_256 *text256Ctor (unsigned int size)
{
    Text_256 *text_256 = (Text_256*) calloc (1, sizeof (Text_256)); 
    text_256->size = size;

    text_256->buffer = (__m256i*) aligned_alloc (32, size * sizeof (__m256i));
    memset (text_256->buffer, 0, size * sizeof (__m256i));

    printf ("SUCCESS - text_256 ctor\n");

    return text_256;
}

//-----------------------------------------------------------------------------

void text256Dtor (Text_256 *text_256)
{
    text_256->size = deleted_par;

    free (text_256->buffer);
    free (text_256);

    printf ("SUCCESS - text_256 dtor\n");
}

//-----------------------------------------------------------------------------
