#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "cht.h"

#define _CHT_SIZE 20000

#define _CHT_FOREACH(i) \
	for (i = 0; i < _CHT_SIZE; ++i)

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

HashTable *cht_init(hash_fn hf)
{
	HashTable *h = malloc(sizeof(HashTable));
	int i;

	if (!h || !(h->entries = malloc(sizeof(Entry *) * _CHT_SIZE)))
		return NULL;

	h->hf = hf;

	_CHT_FOREACH(i)
	{
		h->entries[i] = NULL;
	}

	return h;
}

void cht_insert(HashTable *h, const char *key, const char *val)
{
	size_t idx = ((h->hf != NULL) ? h->hf(key) : _hash(key)) % _CHT_SIZE;
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
	size_t idx = ((h->hf != NULL) ? h->hf(key) : _hash(key)) % _CHT_SIZE;
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
	size_t bucket = ((h->hf != NULL) ? h->hf(key) : _hash(key)) % _CHT_SIZE;
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

		prev = e, e = prev->next;

		++i;
	}
}

size_t cht_size(HashTable *h)
{
	size_t ret = 0;
	int i;

	_CHT_FOREACH(i)
	{
		if (h->entries[i] != NULL)
			++ret;
	}

	return ret;
}

void cht_free(HashTable *h)
{
	int i;
	_CHT_FOREACH(i)
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
	static int n = 1, i;
	printf("cht_print() Call No. %d:\n", n++);
	puts("----------------------------");

	_CHT_FOREACH(i)
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
