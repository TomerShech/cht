#include <stdio.h>

#include "ll.h"

int main(void)
{
    LL *singers = ll_new();

    LL_Node *michael_jackson = ll_rpush(singers, ll_node_new("Michael Jackson"));
    LL_Node *prince = ll_rpush(singers, ll_node_new("Prince"));
    LL_Node *whitney_houston = ll_rpush(singers, ll_node_new("Whitney Houston"));

    const int ages[] = {50, 57, 48};

    LL_Iterator *iter = ll_iter_new(singers, LL_DIR_HEAD);
    LL_Node *n;
    int i = 0;

    while ((n = ll_iter_next(iter)))
    {
        printf("%s 💀 at %d\n", n->val, ages[i++]);
    }

    ll_iter_free(iter);

    ll_free(singers); /* Kill 'em all */

    return 0;
}
