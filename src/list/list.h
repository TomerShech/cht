#ifndef COR_LIST_H
#define COR_LIST_H

#include <stdlib.h>

/* Enums */

/* -------------------------------------- */

typedef enum
{
    LIST_DIR_HEAD,
    LIST_DIR_TAIL
} list_dir;

/* Structures */

/* -------------------------------------- */

typedef struct list_node
{
    struct list_node *prev;
    struct list_node *next;
    void *val;
} list_node;

typedef struct
{
    list_node *next;
    list_dir dir;
} list_iterator;

typedef struct
{
    list_node *head;
    list_node *tail;
    unsigned int len;
    void (*free)(void *val);
    int (*cmp)(void *a, void *b);
} list;

/* -------------------------------------- */

/* Functions */

/* -------------------------------------- */

list_node *list_node_new(void *val);

/* -------------------------------------- */

list_iterator *list_iter_new(list *list, list_dir dir);
list_iterator *list_iter_new_from_node(list_node *node, list_dir dir);
list_node *list_iter_next(list_iterator *this);
void list_iter_free(list_iterator *this);

/* -------------------------------------- */

list *list_new(void);
list_node *list_append(list *this, list_node *node);
list_node *list_prepend(list *this, list_node *node);
list_node *list_find(list *this, void *val);
list_node *list_at(list *this, int index);
list_node *list_pop(list *this);
list_node *list_shift(list *this);
void list_remove(list *this, list_node *node);
void list_free(list *this);

/* -------------------------------------- */

#endif /* COR_LIST_H */
