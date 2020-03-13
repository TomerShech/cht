#include <stdio.h>

#include "hash.h"

int main(void)
{
    const char *key = "string";

    printf("%u\n", hash_djb2(key));  /* 479440892 */
    printf("%u\n", hash_sdbm(key));  /* 2838898737 */
    printf("%u\n", hash_fnv1a(key)); /* 398550328 */

    return 0;
}
