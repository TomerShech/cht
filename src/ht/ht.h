#ifndef COR_HT_H
#define COR_HT_H

#include <stddef.h> /* size_t */
#include <stdint.h> /* uint32_t */

/*
	the custom hash function signature must be as following:
	`<an unsigned integer type> hash_fn(const char *);`
	(return an unsigned integer and take a constant string).
*/
typedef uint32_t (*hash_fn)(const char *);

typedef struct entry
{
	char *key;
	char *val;
	struct entry *next;
} entry;

typedef struct
{
	/* an array of entry pointers */
	entry **entries;
	/* a user can supply a custom hash function for the hash table to use */
	hash_fn fn;
	/* number of entries in the hash table */
	size_t size;
} hash_table;

/*
	a custom hash function is optional, pass a NULL pointer to use the default one.
	size is also optional, pass 0 to use the default value.
*/
hash_table *ht_new(hash_fn fn, size_t size);
void ht_insert(hash_table *self, const char *key, const char *val);
char *ht_get(hash_table *self, const char *key);
void ht_delete(hash_table *self, const char *key);
size_t ht_size(hash_table *self);
void ht_free(hash_table *self);
void ht_print(hash_table *self);
/*
	print information about the table, useful for debugging purposes.
	example output:
		ht_print() Call No. 1:
		----------------------------
		bucket #4660 ('John': 'programmer')
		bucket #6908 ('Joanna': 'singer')
		bucket #13445 ('Emily': 'artist')
*/

#endif /* COR_HT_H */
