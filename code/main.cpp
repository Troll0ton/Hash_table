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

    Text_256 *text_256 = strTranslator256Bits (text);  //translate to 256 bits format
    printf ("SUCCESS - translating to 256-bit format\n");

    //compareHashFunctions (text);
    searchingAll (text);
    //searchingAll256 (text_256);
    printf ("SUCCESS - process finished\n");

    textDtor (text);
    text256Dtor (text_256);

    return 0;
}

//-----------------------------------------------------------------------------