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
#include <math.h>

//-----------------------------------------------------------------------------

const int deleted_par = 0xBEDBAD;
const int hash_size = 1000;

//-----------------------------------------------------------------------------

typedef struct Text
{
    char **buffer;
    unsigned int size;
} Text;

//----------------------------------------------------------------------------

#endif //COMMON_H