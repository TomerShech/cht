#ifndef COR_LL_H
#define COR_LL_H

typedef enum
{
    LL_DIR_HEAD,
    LL_DIR_TAIL
} LL_Dir;

typedef struct LL_Node
{
    struct LL_Node *prev;
    struct LL_Node *next;
    void *val;
} LL_Node;

typedef struct
{
    LL_Node *head;
    LL_Node *tail;
    unsigned int len;
    void (*free)(void *val);
    int (*match)(void *a, void *b);
} LL;

typedef struct
{
    LL_Node *next;
    LL_Dir dir;
} LL_Iterator;

LL_Node *ll_node_new(void *val);

LL *ll_new(void);

LL_Node *ll_rpush(LL *self, LL_Node *node);

LL_Node *ll_lpush(LL *self, LL_Node *node);

LL_Node *ll_find(LL *self, void *val);

LL_Node *ll_at(LL *self, int index);

LL_Node *ll_rpop(LL *self);

LL_Node *ll_lpop(LL *self);

void ll_remove(LL *self, LL_Node *node);

void ll_free(LL *self);

LL_Iterator *ll_iter_new(LL *list, LL_Dir dir);

LL_Iterator *ll_iter_new_from_node(LL_Node *node, LL_Dir dir);

LL_Node *ll_iter_next(LL_Iterator *self);

void ll_iter_free(LL_Iterator *self);

#endif /* COR_LL_H */
