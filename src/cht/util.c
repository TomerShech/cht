#include <stdlib.h>
#include <string.h>

#include "util.h"

char *u_dupstr(const char *s)
{
    size_t len = strlen(s) + 1;
    char *p = malloc(len);

    return p ? memcpy(p, s, len) : NULL;
}
