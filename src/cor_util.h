#ifndef COR_UTIL_H
#define COR_UTIL_H

#include <stdio.h>

/* cu prefix - cor util */

void cu_fuk(const char *fmt, ...);
long cu_filelen(FILE *fp);
FILE *cu_safe_fopen(const char *p, const char *m);
void *cu_safe_malloc(size_t n);
char *cu_dupstr(const char *s);
char *cu_readfile(const char *path);
char *cu_readfile_alt(const char *path);

#endif /* COR_UTIL_H */
