#include <stdio.h>
#include <stdlib.h>

#include "../src/cor_util.h"

int main(void)
{
    char *s = cu_readfile("LICENSE");
    FILE *fp = cu_safe_fopen("LICENSE", "r");

    printf("Contents:\n%s\nLength (in bytes): %lu\n", s, cu_filelen(fp));

    free(s);
    
    return 0;
}
