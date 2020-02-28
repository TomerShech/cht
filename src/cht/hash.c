#include "hash.h"

unsigned long hash_djb2(const char *str)
{
    unsigned long hash = 5381UL;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

unsigned long hash_sdbm(const char *str)
{
    unsigned long hash = 0UL;
    int c;

    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

unsigned long hash_fnv1a(const char *str)
{
    unsigned long hash = 0x811c9dc5UL;

    while (*str)
    {
        hash ^= (unsigned char)*str++;
        hash *= 0x01000193UL;
    }

    return hash;
}
