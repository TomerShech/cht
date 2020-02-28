# Cor - C Data Structures implementations

Cor (Latin for Heart ❤️) is a collection of minimalist & useful data structures libraries for C.
Written in a way that shouldn't interfere with the rest of your project, you can easily just drag and drop the `.c` file and its header and compile them along with it.
At the moment, a Hash Table and a Doubly Linked List are available. Cor is at a very early stage, but also actively developed.

## Installation (Unix-like)
Once you've cloned the repo, you can use `make TARGET=<library name without lib prefix>` to create & install it.
```
git clone https://github.com/TomerShech/cor.git && cd cor
mkdir -p build lib # important, without this line make will fail!

make TARGET=cht # create the hash table static library
make TARGET=ll # create the linked list static library

(sudo) make install TARGET=<name> # install the library
(sudo) make uninstall TARGET=<name> # uninstall it
```

## Example
After installation, include the header file and you're good to go. It is very well-commented, and the functions names are pretty much self-explanatory.
```c
#include <stdio.h>
#include <cht.h>

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

	/* remove an entry from people */
	cht_delete(people, "John");

	cht_print(people);

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

Compile this code with `clang/gcc cht_example.c -lcht -o example` and then run `./example`:

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
Pull requests are warmly welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
This project is licensed under the MIT License. See the [LICENSE](https://github.com/TomerShech/cor/blob/master/LICENSE) file for further reference.
