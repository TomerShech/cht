#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "cht.h"

#define DEFAULT_TABLE_SIZE 20000

#define TABLE_FOREACH(i) \
	for (i = 0; i < h->size; ++i)

#define TABLE_IDX() \
	((h->hf != NULL) ? h->hf(key) : _hash(key)) % h->size

struct _Entry
{
	char *key;
	char *val;
	struct _Entry *next;
};

struct _HashTable
{
	/* an array of Entry pointers */
	Entry **entries;
	/* a user can supply a custom hash function for the hash table to use */
	hash_fn hf;
	/* number of entries in the hash table */
	size_t size;
};

static size_t _hash(const char *s)
{
	size_t hash = 5381;
	int c;

	while ((c = *s++))
		hash = ((hash << 5) + hash) + c;

	return hash;
}

static Entry *_pair(const char *key, const char *val)
{
	Entry *e = malloc(sizeof(Entry));

	if (!e || !(e->key = malloc(strlen(key) + 1)) || !(e->val = malloc(strlen(val) + 1)))
		return NULL;

	strcpy(e->key, key);
	strcpy(e->val, val);

	e->next = NULL;

	return e;
}

HashTable *cht_init(hash_fn hf, size_t size)
{
	HashTable *h = malloc(sizeof(HashTable));
	size_t i;

	if (!h)
		return NULL;

	h->hf = hf;
	h->size = (size == 0) ? DEFAULT_TABLE_SIZE : size;

	if (!(h->entries = malloc(sizeof(Entry *) * h->size)))
		return NULL;

	TABLE_FOREACH(i)
	{
		h->entries[i] = NULL;
	}

	return h;
}

void cht_insert(HashTable *h, const char *key, const char *val)
{
	size_t idx = TABLE_IDX();
	Entry *e = h->entries[idx], *prev;

	if (e == NULL)
	{
		h->entries[idx] = _pair(key, val);
		return;
	}

	while (e != NULL)
	{
		if (!strcmp(e->key, key))
		{
			free(e->val);
			if ((e->val = malloc(strlen(val) + 1)) != NULL)
			{
				strcpy(e->val, val);
				return;
			}
		}

		prev = e;
		e = prev->next;
	}

	prev->next = _pair(key, val);
}

char *cht_get(HashTable *h, const char *key)
{
	size_t idx = TABLE_IDX();
	Entry *e = h->entries[idx];

	while (e != NULL)
	{
		if (!strcmp(e->key, key))
			return e->val;

		e = e->next;
	}

	return NULL;
}

void cht_delete(HashTable *h, const char *key)
{
	size_t bucket = TABLE_IDX();
	Entry *e = h->entries[bucket], *prev;
	int i = 0;

	if (e == NULL)
		return;

	while (e != NULL)
	{
		if (!strcmp(e->key, key))
		{
			if (i == 0 && e->next == NULL)
				h->entries[bucket] = NULL;

			if (i == 0 && e->next != NULL)
				h->entries[bucket] = e->next;

			if (i != 0 && e->next == NULL)
				prev->next = NULL;

			if (i != 0 && e->next != NULL)
				prev->next = e->next;

			free(e->key);
			free(e->val);
			free(e);

			return;
		}

		prev = e;
		e = prev->next;

		++i;
	}
}

size_t cht_size(HashTable *h)
{
	size_t ret = 0, i;

	TABLE_FOREACH(i)
	{
		if (h->entries[i] != NULL)
			++ret;
	}

	return ret;
}

void cht_free(HashTable *h)
{
	size_t i;
	TABLE_FOREACH(i)
	{
		Entry *e = h->entries[i];

		if (e)
		{
			free(e->key);
			free(e->val);
			free(e);
		}
	}

	free(h->entries);
	free(h);
}

void cht_print(HashTable *h)
{
	static unsigned int n = 1, i;
	printf("cht_print() Call No. %d:\n", n++);
	puts("----------------------------");

	TABLE_FOREACH(i)
	{
		Entry *e = h->entries[i];

		if (e == NULL)
			continue;

		printf("bucket #%d ", i);

		while (1)
		{
			printf("('%s': '%s') ", (char *)e->key, (char *)e->val);

			if (e->next == NULL)
				break;

			e = e->next;
		}

		puts("");
	}
}
