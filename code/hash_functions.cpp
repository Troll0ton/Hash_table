#include "../include/hash_functions.h"

//-----------------------------------------------------------------------------
// hf <=> hash function
//-----------------------------------------------------------------------------

unsigned int const_hf (char *line)
{
    return 1;
}

//-----------------------------------------------------------------------------

unsigned int first_sym_hf (char *line)
{
    return (line[0] % HASH_SIZE);
}

//-----------------------------------------------------------------------------

unsigned int len_hf (char *line)
{
    return (strlen (line) % HASH_SIZE);
}

//-----------------------------------------------------------------------------

unsigned int sum_hf (char *line)
{
    unsigned int hash_sum = 0;
    unsigned int line_len = strlen (line);

    for(unsigned int i = 0; i < line_len; i++)
    {
        hash_sum = (hash_sum + line[i]);
    }

    return (hash_sum % HASH_SIZE);
}

//-----------------------------------------------------------------------------

unsigned int round_right_hf (char *line)
{
    unsigned int hash_sum = 0;
    unsigned int line_len = strlen (line);

    for(unsigned int i = 0; i < line_len; i++)
    {
        hash_sum = (hash_sum >> 1) | (hash_sum << (32 - 1));
        hash_sum ^= line[i];
    }

    return (hash_sum % HASH_SIZE);
}

//-----------------------------------------------------------------------------

unsigned int round_left_hf (char *line)
{
    unsigned int hash_sum = 0;
    unsigned int line_len = strlen (line);

    for(unsigned int i = 0; i < line_len; i++)
    {
        hash_sum = (hash_sum << 1) | (hash_sum >> (32 - 1));
        hash_sum ^= line[i];
    }

    return (hash_sum % HASH_SIZE);
}

//-----------------------------------------------------------------------------

unsigned int super_secret_hf (char *line)
{
    unsigned int hash_sum = 0;
    unsigned int hash_par = 1;
    unsigned int hash_base = HASH_SIZE + 1;
    unsigned int line_len = strlen (line);

    for(unsigned int i = 0; i < line_len; i++)
    {
        hash_sum += (unsigned int) (line[i]) * hash_par;
        hash_par *= hash_base;
    }

    return (hash_sum % HASH_SIZE);
}

//-----------------------------------------------------------------------------

unsigned int horner_hf (char *line)
{
    unsigned int hash_sum = 0;

    for (int i = 0; line[i] != '\0'; i++)
    {
        hash_sum = ((HASH_SIZE + 1) * hash_sum + line[i]) % HASH_SIZE;
    }
    
    hash_sum = (hash_sum * 2 + 1) % HASH_SIZE;

    return hash_sum;
}

//-----------------------------------------------------------------------------