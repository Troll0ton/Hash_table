#include "../include/hash_table.h"
#include "../include/input_utils.h"
#include "../include/hash_functions.h"
#include "../include/text_utils.h"

//-----------------------------------------------------------------------------

int main()
{
    FILE *file = fopen ("text.txt", "r+");
    char *buffer = fileReader (file); //read file
    fclose (file);
    printf ("SUCCESS - reading\n");

    Text *text = bufferSeparator (buffer);  //separate into words
    printf ("SUCCESS - separating %u words\n", text->size);

    char *buffer_256 = strTranslator256Bits (text);  //translate to 256 bits format
    Text *text_256 = bufferSeparator256Bit (buffer_256, text->size);
    printf ("SUCCESS - translating to 256-bit format\n");

    //compareHashFunctions (text);
    //searchingAll (text, strcmp);
    //searchingAll (text_256, strcmp);
    searchingAll (text_256, strcmpAvx);

    printf ("SUCCESS - process finished\n");

    textDtor (text);
    textDtor (text_256);
    free (buffer);
    free (buffer_256);

    return 0;
}

//-----------------------------------------------------------------------------