//! @file text_utils.h

#ifndef   TEXT_UTILS_H
#define   TEXT_UTILS_H

//-----------------------------------------------------------------------------

#include "common.h"

//-----------------------------------------------------------------------------

unsigned int findNumOfWords (char *buffer);
Text *bufferSeparator (char *buffer);
char *strTranslator256Bits (Text *text);
Text *bufferSeparator256Bit (char *buffer, int size);
Text *textCtor (char *buffer, int size);
void textDtor (Text *text);

//-----------------------------------------------------------------------------

#endif //TEXT_UTILS_H