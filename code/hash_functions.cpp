#include "../include/hash_functions.h"

//-----------------------------------------------------------------------------
// hf <=> hash function
//-----------------------------------------------------------------------------

unsigned int constHf (char *line)
{
    return 1;
}

//-----------------------------------------------------------------------------

unsigned int firstSymHf (char *line)
{
    return (line[0] % hash_size);
}

//-----------------------------------------------------------------------------

unsigned int lenHf (char *line)
{
    return (strlen (line) % hash_size);
}

//-----------------------------------------------------------------------------

unsigned int sumHf (char *line)
{
    unsigned int hash_sum = 0;
    unsigned int line_len = strlen (line);

    for(unsigned int i = 0; i < line_len; i++)
    {
        hash_sum = (hash_sum + line[i]);
    }

    return (hash_sum % hash_size);
}

//-----------------------------------------------------------------------------

unsigned int roundRightHf (char *line)
{
    unsigned int hash_sum = 0;
    unsigned int line_len = strlen (line);

    for(unsigned int i = 0; i < line_len; i++)
    {
        hash_sum = (hash_sum >> 1) | (hash_sum << (32 - 1));
        hash_sum ^= line[i];
    }

    return (hash_sum % hash_size);
}

//-----------------------------------------------------------------------------

unsigned int roundLeftHf (char *line)
{
    unsigned int hash_sum = 0;
    unsigned int line_len = strlen (line);

    for(unsigned int i = 0; i < line_len; i++)
    {
        hash_sum = (hash_sum << 1) | (hash_sum >> (32 - 1));
        hash_sum ^= line[i];
    }

    return (hash_sum % hash_size);
}

//-----------------------------------------------------------------------------

unsigned int superSecretHf (char *line)
{
    unsigned int hash_sum = 0;
    unsigned int hash_par = 1;
    unsigned int hash_base = hash_size + 1;
    unsigned int line_len = strlen (line);

    for(unsigned int i = 0; i < line_len; i++)
    {
        hash_sum += (unsigned int) (line[i]) * hash_par;
        hash_par *= hash_base;
    }

    return (hash_sum % hash_size);
}

//-----------------------------------------------------------------------------