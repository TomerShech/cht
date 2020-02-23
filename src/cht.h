#ifndef CHT_H
#define CHT_H

#include <stddef.h> /* for size_t */

#define _CHT_SIZE 20000

typedef struct Entry
{
	char *key;
	char *val;
	struct Entry *next;
} Entry;

/*
	the custom hash function signature must be as following:
	`size_t hash_fn(const char *);`
	(return an unsigned integer and take a constant string)
*/
typedef size_t (*hash_fn)(const char *);

typedef struct
{
	/* an array of Entry pointers */
	Entry **entries;
	/* a user can supply a custom hash function for the hash table to use */
	hash_fn hf;
} HashTable;

/* the custom hash function is optional, pass NULL to use the default one provided by cht */
HashTable *cht_init(hash_fn hf);

void cht_insert(HashTable *h, const char *key, const char *val);

char *cht_get(HashTable *h, const char *key);

void cht_delete(HashTable *h, const char *key);

void cht_free(HashTable *h);

/*
	print information about the table, useful for debugging purposes.
	example output:
		
		cht_print() Call No. 1:
		----------------------------
		bucket #4660 ('John': 'programmer')
		bucket #6908 ('Joanna': 'singer')
		bucket #13445 ('Emily': 'artist')
*/
void cht_print(HashTable *h);

#endif /* CHT_H */
