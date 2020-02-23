#ifndef CHT_H
#define CHT_H

#include <stddef.h> /* for size_t */

/*
	the custom hash function signature must be as following:
	`size_t hash_fn(const char *);`
	(return an unsigned integer and take a constant string)
*/
typedef size_t (*hash_fn)(const char *);

typedef struct _Entry Entry;
typedef struct _HashTable HashTable;

/* the custom hash function is optional, pass NULL to use the default one provided by cht */
HashTable *cht_init(hash_fn hf);

void cht_insert(HashTable *h, const char *key, const char *val);

char *cht_get(HashTable *h, const char *key);

void cht_delete(HashTable *h, const char *key);

size_t cht_size(HashTable *h);

void cht_free(HashTable *h);

void cht_print(HashTable *h);
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
