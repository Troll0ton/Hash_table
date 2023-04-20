//! @file input_utils.h

#ifndef   INPUT_UTILS_H
#define   INPUT_UTILS_H

//-----------------------------------------------------------------------------

#include "common.h"

//-----------------------------------------------------------------------------

#define SAME_LINES 0
#define SKIP_ARG 1

//-----------------------------------------------------------------------------

char *file_reader (FILE *file);
unsigned int find_file_size (FILE *file);
unsigned int find_num_of_words (char *buffer);
Text *buffer_separator (char *buffer);

//-----------------------------------------------------------------------------

#endif //INPUT_UTILS_H