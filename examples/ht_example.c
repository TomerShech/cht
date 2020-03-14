#include <stdio.h>
#include <cor/ht.h>

/* a very simple hash function that was presented in K&R version 2 */
unsigned int kr_hash(const char *s)
{
	unsigned int hash;

	for (hash = 0; *s != '\0'; ++s)
		hash = *s + 31 * hash;

	return hash;
}

int main(void)
{
	/* use the default hash function provided by ht */
	HashTable *people = ht_new(NULL, 0);
	/* OR use a custom hash function, which must return
	an unsigned integer and take a constant string */
	HashTable *animals = ht_new(kr_hash, 10);

	/* insert some key-value pairs into the people table */
	ht_insert(people, "John", "programmer");
	ht_insert(people, "Emily", "artist");
	ht_insert(people, "Joanna", "singer");

	ht_print(people);
	/*
		ht_print() Call No. 1:
		----------------------------
		bucket #4660 ('John': 'programmer')
		bucket #6908 ('Joanna': 'singer')
		bucket #13445 ('Emily': 'artist')
	*/

	/* remove an entry from people */
	ht_delete(people, "John");

	ht_print(people);
	/*
		ht_print() Call No. 2:
		----------------------------
		bucket #6908 ('Joanna': 'singer')
		bucket #13445 ('Emily': 'artist')
	*/

	ht_insert(animals, "Elephant", "Mammal");
	ht_insert(animals, "Snake", "Reptile");
	ht_insert(animals, "Clownfish", "Pomacentridae");

	ht_print(animals);
	/*
		ht_print() Call No. 3:
		----------------------------
		bucket #661 ('Clownfish': 'Pomacentridae')
		bucket #4817 ('Elephant': 'Mammal')
		bucket #5888 ('Snake': 'Reptile')


		As you can see, the order in which the entries are inserted is not
		guaranteed to be identical to the order the functions were called.
	*/

	/* get a value from the table using its key */
	char *nemo = ht_get(animals, "Clownfish");

	puts(nemo); /* prints 'Pomacentridae' */

	printf("There are %lu entries in the people hash table\n", ht_size(people));

	/* deallocate the memory that was used by the tables */
	ht_free(animals);
	ht_free(people);

	return 0;
}
