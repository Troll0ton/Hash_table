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

const int deleted_par = 0xBEDBAD;
const int hash_size = 1000;

//-----------------------------------------------------------------------------

typedef struct Text
{
    char **buffer;
    unsigned int size;
} Text;

//----------------------------------------------------------------------------

typedef struct Text_256
{
    __m256i *buffer;
    unsigned int size;
} Text_256;

//----------------------------------------------------------------------------

#endif //COMMON_H