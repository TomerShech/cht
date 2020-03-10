#ifndef COR_LL_H
#define COR_LL_H

/* Enums */

typedef enum
{
    LL_DIR_HEAD,
    LL_DIR_TAIL
} LL_Dir;

/* Structures */

typedef struct LL_Node
{
    struct LL_Node *prev;
    struct LL_Node *next;
    void *val;
} LL_Node;

typedef struct
{
    LL_Node *next;
    LL_Dir dir;
} LL_Iterator;

typedef struct
{
    LL_Node *head;
    LL_Node *tail;
    unsigned int len;
    void (*free)(void *val);
    int (*cmp)(void *a, void *b);
} LL;

/* Functions */

LL_Node *ll_node_new(void *val);

LL_Iterator *ll_iter_new(LL *list, LL_Dir dir);
LL_Iterator *ll_iter_new_from_node(LL_Node *node, LL_Dir dir);
LL_Node *ll_iter_next(LL_Iterator *self);
void ll_iter_free(LL_Iterator *self);

LL *ll_new(void);
LL_Node *ll_prepend(LL *self, LL_Node *node);
LL_Node *ll_append(LL *self, LL_Node *node);
LL_Node *ll_shift(LL *self);
LL_Node *ll_pop(LL *self);
LL_Node *ll_find(LL *self, void *val);
LL_Node *ll_at(LL *self, int index);
void ll_remove(LL *self, LL_Node *node);
void ll_free(LL *self);

#endif /* COR_LL_H */
