#include <stdio.h>
#include <cor/list.h>

#include "minunit.h"

int tests_run = 0;

static char *test_list_new(void)
{
    list *l = list_new();
    mu_assert("list new, head", l->head == NULL);
    mu_assert("list new, tail", l->tail == NULL);
    mu_assert("list new, free", l->free == NULL);
    mu_assert("list new, compare", l->cmp == NULL);
    mu_assert("list new, length", l->len == 0);
    list_free(l);
    return 0;
}

static char *all_tests(void)
{
    mu_run_test(test_list_new);
    return 0;
}

int main(void)
{
    char *result = all_tests();
    printf("%s\nTests run: %d\n", result != 0 ? result : "ALL TESTS PASSED", tests_run);
    return result != 0;
}
