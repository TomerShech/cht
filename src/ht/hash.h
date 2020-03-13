/*
This file contains different hash functions with different results.
Each have their pros and cons, use whatever you feel like using.
I chose djb2 as the default one for ht, but you're welcome to change it (in ht.c) 
so it matches your preferences.
*/

#ifndef COR_HASH_H
#define COR_HASH_H

#include <stdint.h>

uint32_t hash_djb2(const char *str);
uint32_t hash_sdbm(const char *str);
uint32_t hash_fnv1a(const char *str);

#endif /* COR_HASH_H */
