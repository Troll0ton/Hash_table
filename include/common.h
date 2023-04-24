//! @file common.h

#ifndef COMMON_H
#define COMMON_H

//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <immintrin.h>
#include <cctype>
#include <assert.h>
#include <locale.h>
#include <limits.h>
#include <stdint.h>

//-----------------------------------------------------------------------------

const int DELETED_PAR = 0xBEDBAD;
const int HASH_SIZE = 1000;

//-----------------------------------------------------------------------------

typedef struct Text
{
    char **buffer;
    unsigned int size;
} Text;

//----------------------------------------------------------------------------

#endif //COMMON_H