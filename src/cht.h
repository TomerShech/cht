#ifndef CHT_H
#define CHT_H

#include <stddef.h> /* for size_t */

/*
	the custom hash function signature must be as following:
	`size_t hash_fn(const char *);`
	(return an unsigned integer and take a constant string).
*/
typedef size_t (*hash_fn)(const char *);

typedef struct _Entry
{
	char *key;
	char *val;
	struct _Entry *next;
} Entry;

typedef struct _HashTable
{
	/* an array of Entry pointers */
	Entry **entries;
	/* a user can supply a custom hash function for the hash table to use */
	hash_fn fn;
	/* number of entries in the hash table */
	size_t size;
} HashTable;

/*
	a custom hash function is optional, pass a NULL pointer to use the default one.
	size is also optional, pass 0 to use the default value.
*/
HashTable *cht_init(hash_fn fn, size_t size);

void cht_insert(HashTable *self, const char *key, const char *val);

char *cht_get(HashTable *self, const char *key);

void cht_delete(HashTable *self, const char *key);

size_t cht_size(HashTable *self);

void cht_free(HashTable *self);

void cht_print(HashTable *self);
/*
	print information about the table, useful for debugging purposes.
	example output:

		cht_print() Call No. 1:
		----------------------------
		bucket #4660 ('John': 'programmer')
		bucket #6908 ('Joanna': 'singer')
		bucket #13445 ('Emily': 'artist')
*/

#endif /* CHT_H */
