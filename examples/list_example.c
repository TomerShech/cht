#include <stdio.h>

#include <cor/list.h>

int main(void)
{
    list *singers = list_new();

    list_node *michael_jackson = list_append(singers, list_node_new("Michael Jackson"));
    list_node *prince = list_append(singers, list_node_new("Prince"));
    list_node *whitney_houston = list_append(singers, list_node_new("Whitney Houston"));

    const int ages[] = {50, 57, 48};

    list_reverse(singers);

    list_iterator *iter = list_iter_new(singers, LIST_DIR_HEAD);
    list_node *n;
    int i = 0;

    while ((n = list_iter_next(iter)))
        printf("%s 💀 at %d\n", (char *)n->val, ages[i++]);

    list_iter_free(iter);
    list_free(singers); /* Kill 'em all */

    return 0;
}
