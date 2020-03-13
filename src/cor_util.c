#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "cor_util.h"

void cu_fuk(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);

    vfprintf(stderr, fmt, ap);
    perror(" ");

    va_end(ap);
    exit(1);
}

long cu_filelen(FILE *fp)
{
    long ret;

    fseek(fp, 0L, SEEK_END);
    ret = ftell(fp);
    rewind(fp);

    return ret;
}

FILE *cu_safe_fopen(const char *p, const char *m)
{
    FILE *ret = fopen(p, m);

    if (ret == NULL)
        cu_fuk("Cannot open file '%s'", p);

    return ret;
}

void *cu_safe_malloc(size_t n)
{
    void *ret = malloc(n);

    if (ret == NULL)
        cu_fuk("Couldn't allocate %lu bytes of memory", n);

    return ret;
}

char *cu_dupstr(const char *s)
{
    size_t len = strlen(s) + 1;
    char *p = malloc(len);

    return p ? memcpy(p, s, len) : NULL;
}

char *cu_readfile(const char *path)
{
    FILE *fp = cu_safe_fopen(path, "r");
    long len = cu_filelen(fp);
    char *buf = malloc(len + 1);

    buf[len] = '\0';

    fread(buf, 1, len, fp);
    fclose(fp);

    return buf;
}

char *cu_readfile_alt(const char *path)
{
    FILE *fp = cu_safe_fopen(path, "r");
    long len = cu_filelen(fp);
    char *buf = cu_safe_malloc(len + 1);
    int i = 0;
    char c;

    while ((c = getc(fp)) != EOF)
        buf[i++] = c;
    buf[len] = '\0';

    fclose(fp);

    return buf;
}
