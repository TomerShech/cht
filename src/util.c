#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "util.h"

static void fuk(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);

    vfprintf(stderr, fmt, ap);
    perror(" ");

    va_end(ap);
    exit(1);
}

static long filelen(FILE *fp)
{
    long ret;

    fseek(fp, 0L, SEEK_END);
    ret = ftell(fp);
    rewind(fp);

    return ret;
}

static FILE *safe_fopen(const char *p, const char *m)
{
    FILE *ret = fopen(p, m);

    if (ret == NULL)
        fuk("Cannot open file '%s'", p);

    return ret;
}

static void *safe_malloc(size_t n)
{
    void *ret = malloc(n);

    if (ret == NULL)
        fuk("Couldn't allocate %lu bytes of memory", n);

    return ret;
}

char *u_dupstr(const char *s)
{
    size_t len = strlen(s) + 1;
    char *p = malloc(len);

    return p ? memcpy(p, s, len) : NULL;
}

char *u_readfile(const char *path)
{
    FILE *fp = safe_fopen(path, "r");
    long len = filelen(fp);
    char *buf = malloc(len + 1);

    buf[len] = '\0';

    fread(buf, 1, len, fp);
    fclose(fp);

    return buf;
}

char *u_readfile2(const char *path)
{
    FILE *fp = safe_fopen(path, "r");
    long len = filelen(fp);
    char *buf = safe_malloc(len + 1);
    int i = 0;
    char c;

    while ((c = getc(fp)) != EOF)
        buf[i++] = c;
    buf[len] = '\0';

    fclose(fp);

    return buf;
}
