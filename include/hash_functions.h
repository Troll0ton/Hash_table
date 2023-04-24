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

unsigned int const_hf (char *line);
unsigned int first_sym_hf (char *line);
unsigned int len_hf (char *line);
unsigned int sum_hf (char *line);
unsigned int round_right_hf (char *line);
unsigned int round_left_hf (char *line);
unsigned int super_secret_hf (char *line);
unsigned int horner_hf (char *line);

//-----------------------------------------------------------------------------

#endif //HASH_FUNCTIONS_H