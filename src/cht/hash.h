/*
This file contains different hash functions with different results.
Each have their pros and cons, use whatever you feel like using.
I chose djb2 as the default one for cht, but you're welcome to change it (in cht.c) 
so it matches your preferences.
*/

#ifndef COR_HASH_H
#define COR_HASH_H

unsigned long hash_djb2(const char *str);
unsigned long hash_sdbm(const char *str);
unsigned long hash_fnv1a(const char *str);

#endif /* COR_HASH_H */
