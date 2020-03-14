# Cor - C Data Structures implementations

Cor (Latin for Heart ❤️) is a collection of minimalist & useful data structures libraries for C.
Written in a way that shouldn't interfere with the rest of your project, you can easily just drag and drop the `.c` file and its matching header and compile them along with it.
At the moment, a Hash Table and a Doubly Linked List are available. Cor is at a very early stage, but also actively developed.

## Installation (*nix)
Once you've cloned the repo, you can use `make TARGET=<library name without lib prefix>` to create the static library and (optionally) `make install` to copy the headers to `/usr/local/include` and the `*.a` to `/usr/local/lib`.
```sh
git clone https://github.com/TomerShech/cor.git && cd cor
mkdir -p build lib # important, without this line make will fail!

make TARGET=ht # create the hash table static library
make TARGET=list # linked list one

[sudo] make install
```

## Example
After installation, include the header file and you're good to go. It is very well-commented, and the functions names are pretty much self-explanatory.
```c
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

```

Compile this code with `clang/gcc examples/ht_example.c src/cor_util.c -lht -o example` and then run `./example`:

```
ht_print() Call No. 1:
----------------------------
bucket #1980 ('Joanna': 'singer')
bucket #15941 ('Emily': 'artist')
bucket #17364 ('John': 'programmer')
ht_print() Call No. 2:
----------------------------
bucket #1980 ('Joanna': 'singer')
bucket #15941 ('Emily': 'artist')
ht_print() Call No. 3:
----------------------------
bucket #1 ('Clownfish': 'Pomacentridae')
bucket #7 ('Elephant': 'Mammal')
bucket #8 ('Snake': 'Reptile')
Pomacentridae
There are 2 entries in the people hash table
```

## Contributing
Pull requests are warmly welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
This project is licensed under the MIT License. See the [LICENSE](https://github.com/TomerShech/cor/blob/master/LICENSE) file for further reference.
