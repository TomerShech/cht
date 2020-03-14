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

static char *test_node_new(void)
{
    list_node *n = list_node_new("value");
    mu_assert("new node, next", n->next == NULL);
    mu_assert("new node, prev", n->prev == NULL);
    mu_assert("new node, val", n->val == "value");
    return 0;
}

static char *test_iterator_new(void)
{
    list *l = list_new();
    list_iterator *it = list_iter_new(l, LIST_DIR_HEAD);
    mu_assert("new iterator, next", it->next == NULL);
    mu_assert("new iterator, dir", it->dir == LIST_DIR_HEAD);
    list_iter_free(it);
    list_free(l);
    return 0;
}

static char *test_list_reverse(void)
{
    list *l = list_new();

    list_node *j = list_append(l, list_node_new("John"));
    list_node *m = list_append(l, list_node_new("Michaela"));
    list_node *d = list_append(l, list_node_new("Donna"));

    mu_assert("list, head", l->head == j);
    mu_assert("list, tail", l->tail == d);

    list_pop(l);

    mu_assert("list, length", l->len == 2);
    mu_assert("list, tail", l->tail == m);

    list_reverse(l);

    mu_assert("reverse list, head", l->head == m);
    mu_assert("reverse list, tail", l->tail == j);
    mu_assert("reverse list, length", l->len == 2);
    mu_assert("reverse list, head next", l->head->next == j);
    mu_assert("reverse list, tail previous", l->tail->prev == m);
    mu_assert("reverse list, tail next", l->tail->next == NULL);

    list_prepend(l, list_node_new("Chris"));
    list_prepend(l, list_node_new("Diana"));

    mu_assert("list, length", l->len == 4);
    mu_assert("list, head value", l->head->val == "Diana");
    mu_assert("list, tail value", l->tail->val == "John");

    list_reverse(l);
    list_shift(l);

    mu_assert("list, length", l->len == 3);
    mu_assert("list, head value", l->head->val == "Michaela");

    list_free(l);
    return 0;
}

static char *all_tests(void)
{
    mu_run_test(test_list_new);
    mu_run_test(test_node_new);
    mu_run_test(test_iterator_new);
    mu_run_test(test_list_reverse);
    return 0;
}

int main(void)
{
    char *result = all_tests();
    printf("%s\nTests run: %d\n", result != 0 ? result : "ALL TESTS PASSED", tests_run);
    return result != 0;
}
