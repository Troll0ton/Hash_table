//! @file text_utils.h

#ifndef   TEXT_UTILS_H
#define   TEXT_UTILS_H

//-----------------------------------------------------------------------------

#include "common.h"

//-----------------------------------------------------------------------------

unsigned int findNumOfWords (char *buffer);
Text *bufferSeparator (char *buffer);
Text_256 *strTranslator256Bits (Text *text);
Text *textCtor (char *buffer);
void textDtor (Text *text);
Text_256 *text256Ctor (unsigned int size);
void text256Dtor (Text_256 *text_256);

//-----------------------------------------------------------------------------

#endif //TEXT_UTILS_H