//! @file hash_functions.h

#ifndef   HASH_FUNCTIONS_H
#define   HASH_FUNCTIONS_H

//-----------------------------------------------------------------------------

#include "common.h"

//-----------------------------------------------------------------------------

enum Hash_pars
{
    HASH_CONST = 17,
    SIZE_OF_HASH = 4,
};

//-----------------------------------------------------------------------------

unsigned int constHf (char *line);
unsigned int firstSymHf (char *line);
unsigned int lenHf (char *line);
unsigned int sumHf (char *line);
unsigned int roundRightHf (char *line);
unsigned int roundLeftHf (char *line);
unsigned int superSecretHf (char *line);
unsigned int Crc32hf (char *line);

//-----------------------------------------------------------------------------

#endif //HASH_FUNCTIONS_H