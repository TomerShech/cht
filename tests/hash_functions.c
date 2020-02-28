#include <stdio.h>

#include "hash.h"

int main(void)
{
    const char *key = "string";

    printf("%lu\n", hash_djb2(key));  /* 6954031493116 */
    printf("%lu\n", hash_sdbm(key));  /* 2985983639226296369 */
    printf("%lu\n", hash_fnv1a(key)); /* 9504961208554448184 */

    return 0;
}
