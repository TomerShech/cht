#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ht.h"
#include "hash.h"
#include "cor_util.h"

#define DEFAULT_HT_SIZE 20000
#define HT_IDX() \
	(((self->fn != NULL) ? self->fn(key) : hash_djb2(key)) % (self->size))

static Entry *pair(const char *key, const char *val)
{
	Entry *e = malloc(sizeof(Entry));

	if (!e)
		return NULL;

	e->key = cu_dupstr(key);
	e->val = cu_dupstr(val);
	e->next = NULL;

	if (!e->key || !e->val)
	{
		free(e->key);
		free(e->val);
		free(e);
		return NULL;
	}

	return e;
}

HashTable *ht_new(hash_fn fn, size_t size)
{
	HashTable *ret = malloc(sizeof(HashTable));

	if (!ret)
		return NULL;

	ret->fn = fn;
	ret->size = (size == 0) ? DEFAULT_HT_SIZE : size;

	if (!(ret->entries = malloc(sizeof(Entry *) * ret->size)))
		return NULL;

	for (size_t i = 0; i < ret->size; ++i)
		ret->entries[i] = NULL;

	return ret;
}

void ht_insert(HashTable *self, const char *key, const char *val)
{
	size_t idx = HT_IDX();
	Entry *e = self->entries[idx], *prev;

	if (e == NULL)
	{
		self->entries[idx] = pair(key, val);
		return;
	}

	while (e)
	{
		if (strcmp(e->key, key) == 0)
		{
			free(e->val);
			e->val = cu_dupstr(val);
			return;
		}

		prev = e;
		e = prev->next;
	}

	prev->next = pair(key, val);
}

char *ht_get(HashTable *self, const char *key)
{
	Entry *e = self->entries[HT_IDX()];

	while (e)
	{
		if (strcmp(e->key, key) == 0)
			return e->val;

		e = e->next;
	}

	return NULL;
}

void ht_delete(HashTable *self, const char *key)
{
	Entry **prev_next = &self->entries[HT_IDX()];

	for (Entry *e = *prev_next; e != NULL; prev_next = &e->next, e = e->next)
	{
		if (strcmp(e->key, key) == 0)
		{
			*prev_next = e->next;
			free(e->key);
			free(e->val);
			free(e);
			return;
		}
	}
}

size_t ht_size(HashTable *self)
{
	size_t ret = 0;

	for (size_t i = 0; i < self->size; ++i)
	{
		if (self->entries[i] != NULL)
		{
			++ret;
		}
	}

	return ret;
}

void ht_free(HashTable *self)
{
	for (size_t i = 0; i < self->size; ++i)
	{
		Entry *e = self->entries[i];

		if (e)
		{
			free(e->key);
			free(e->val);
			free(e);
		}
	}

	free(self->entries);
	free(self);
}

void ht_print(HashTable *self)
{
	static unsigned int n = 1;
	printf("ht_print() Call No. %d:\n", n++);
	puts("----------------------------");

	for (int i = 0; i < self->size; ++i)
	{
		Entry *e = self->entries[i];

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
