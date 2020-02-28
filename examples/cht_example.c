#include <stdio.h>

#include <cht.h>

/* a very simple hash function that was presented in K&R version 2 */
unsigned long kr_hash(const char *s)
{
	unsigned long hash;

	for (hash = 0; *s != '\0'; ++s)
		hash = *s + 31 * hash;

	return hash;
}

int main(void)
{
	/* use the default hash function provided by cht */
	HashTable *people = cht_init(NULL, 0);
	/* OR use a custom hash function, which must return
	an unsigned integer and take a constant string */
	HashTable *animals = cht_init(kr_hash, 10);

	/* insert some key-value pairs into the people table */
	cht_insert(people, "John", "programmer");
	cht_insert(people, "Emily", "artist");
	cht_insert(people, "Joanna", "singer");

	cht_print(people);
	/*
		cht_print() Call No. 1:
		----------------------------
		bucket #4660 ('John': 'programmer')
		bucket #6908 ('Joanna': 'singer')
		bucket #13445 ('Emily': 'artist')
	*/

	/* remove an entry from people */
	cht_delete(people, "John");

	cht_print(people);
	/*
		cht_print() Call No. 2:
		----------------------------
		bucket #6908 ('Joanna': 'singer')
		bucket #13445 ('Emily': 'artist')
	*/

	cht_insert(animals, "Elephant", "Mammal");
	cht_insert(animals, "Snake", "Reptile");
	cht_insert(animals, "Clownfish", "Pomacentridae");

	cht_print(animals);
	/*
		cht_print() Call No. 3:
		----------------------------
		bucket #661 ('Clownfish': 'Pomacentridae')
		bucket #4817 ('Elephant': 'Mammal')
		bucket #5888 ('Snake': 'Reptile')


		As you can see, the order in which the entries are inserted is not
		guaranteed to be identical to the order the functions were called.
	*/

	/* get a value from the table using its key */
	char *nemo = cht_get(animals, "Clownfish");

	puts(nemo); /* prints 'Pomacentridae' */

	printf("There are %lu entries in the people hash table\n", cht_size(people));

	/* deallocate the memory that was used by the tables */
	cht_free(animals);
	cht_free(people);

	return 0;
}
