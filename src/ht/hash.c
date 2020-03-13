#include "hash.h"

uint32_t hash_djb2(const char *str)
{
    uint32_t hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

uint32_t hash_sdbm(const char *str)
{
    uint32_t hash = 0;
    int c;

    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

uint32_t hash_fnv1a(const char *str)
{
    uint32_t hash = 0x811c9dc5;

    while (*str)
    {
        hash ^= (unsigned char)*str++;
        hash *= 0x01000193;
    }

    return hash;
}
