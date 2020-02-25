#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "cht.h"
#include "hash.h"

#define DEFAULT_HT_SIZE 20000
#define HT_IDX() \
	((self->fn != NULL) ? self->fn(key) : hash_djb2(key)) % self->size

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

HashTable *cht_init(hash_fn fn, size_t size)
{
	HashTable *ret = malloc(sizeof(HashTable));
	size_t i;

	if (!ret)
		return NULL;

	ret->fn = fn;
	ret->size = (size == 0) ? DEFAULT_HT_SIZE : size;

	if (!(ret->entries = malloc(sizeof(Entry *) * ret->size)))
		return NULL;

	for (i = 0; i < ret->size; ++i)
		ret->entries[i] = NULL;

	return ret;
}

void cht_insert(HashTable *self, const char *key, const char *val)
{
	size_t idx = HT_IDX();
	Entry *e = self->entries[idx], *prev;

	if (e == NULL)
	{
		self->entries[idx] = _pair(key, val);
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

char *cht_get(HashTable *self, const char *key)
{
	size_t idx = HT_IDX();
	Entry *e = self->entries[idx];

	while (e != NULL)
	{
		if (!strcmp(e->key, key))
			return e->val;

		e = e->next;
	}

	return NULL;
}

void cht_delete(HashTable *self, const char *key)
{
	size_t bucket = HT_IDX();
	Entry *e = self->entries[bucket], *prev;
	int i = 0;

	if (e == NULL)
		return;

	while (e != NULL)
	{
		if (!strcmp(e->key, key))
		{
			if (i == 0 && e->next == NULL)
				self->entries[bucket] = NULL;

			if (i == 0 && e->next != NULL)
				self->entries[bucket] = e->next;

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

size_t cht_size(HashTable *self)
{
	size_t ret = 0, i;

	for (i = 0; i < self->size; ++i)
	{
		if (self->entries[i] != NULL)
			++ret;
	}

	return ret;
}

void cht_free(HashTable *self)
{
	size_t i;
	for (i = 0; i < self->size; ++i)
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

void cht_print(HashTable *self)
{
	static unsigned int n = 1, i;
	printf("cht_print() Call No. %d:\n", n++);
	puts("----------------------------");

	for (i = 0; i < self->size; ++i)
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
