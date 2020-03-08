#include <stdio.h>
#include <stdlib.h>

#include "../src/util.h"

int main(void)
{
    char *s = u_readfile("LICENSE");
    
    puts(s);
    free(s);
    
    return 0;
}
