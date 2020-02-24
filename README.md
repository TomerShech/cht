# cht - C hash table implementation

cht will be useable as a library in the near future.
Adding more useful data structures (that C lacks) such as Linked Lists and Dynamic arrays is also on the To-Do list.

## Installation
Clone the repo and just drop `cht.h` & `cht.c` right in. They are written in a way that shouldn't interfere with the rest of your project.
```
git clone https://github.com/TomerShech/cht.git
cd cht
cp src/cht.* your-project-directory/
```

## Example usage
Include `cht.h` and you're good to go. It is very well-commented, and the functions names are pretty much self-explanatory.
```c
#include <stdio.h>

#include "cht.h"

/* forward declaration */
size_t kr_hash(const char *s);

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

/* a very simple hash function that was presented in K&R version 2 */
size_t kr_hash(const char *s)
{
	size_t hash;

	for (hash = 0; *s != '\0'; ++s)
		hash = *s + 31 * hash;

	return hash;
}
```

Output:
```
cht_print() Call No. 1:
----------------------------
bucket #4660 ('John': 'programmer') 
bucket #6908 ('Joanna': 'singer') 
bucket #13445 ('Emily': 'artist') 
cht_print() Call No. 2:
----------------------------
bucket #6908 ('Joanna': 'singer') 
bucket #13445 ('Emily': 'artist') 
cht_print() Call No. 3:
----------------------------
bucket #1 ('Clownfish': 'Pomacentridae') 
bucket #7 ('Elephant': 'Mammal') 
bucket #8 ('Snake': 'Reptile') 
Pomacentridae
There are 2 entries in the people hash table
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
This project is licensed under the MIT License. See the [LICENSE](https://github.com/TomerShech/cht/blob/master/LICENSE) file for further reference.
