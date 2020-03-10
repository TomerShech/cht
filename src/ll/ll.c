#include <stdlib.h>

#include "ll.h"

/* LL_Node */

/* Allocate a new LL_Node struct with the given value `val`. Return it, or NULL on failure */

LL_Node *ll_node_new(void *val)
{
    LL_Node *self = malloc(sizeof(LL_Node));

    if (!self)
        return NULL;

    self->prev = NULL;
    self->next = NULL;
    self->val = val;

    return self;
}

/* ---------------------------------------- */

/* LL_Iterator */

/*
  * Allocate a new LL_Iterator struct from the list `list` and direction `dir`.
  * Return it, or NULL on failure
*/

LL_Iterator *ll_iter_new(LL *list, LL_Dir dir)
{
    LL_Node *node = dir == LL_DIR_HEAD ? list->head : list->tail;
    return ll_iter_new_from_node(node, dir);
}

/* Allocate a new LL_Iterator with the given start node. Return it, or NULL on failure */

LL_Iterator *ll_iter_new_from_node(LL_Node *node, LL_Dir dir)
{
    LL_Iterator *self = malloc(sizeof(LL_Iterator));

    if (!self)
        return NULL;

    self->next = node;
    self->dir = dir;

    return self;
}

/* Return the next LL_Node or NULL when no more nodes are left in the list */

LL_Node *ll_iter_next(LL_Iterator *self)
{
    LL_Node *cur = self->next;

    if (cur)
        self->next = self->dir == LL_DIR_HEAD ? cur->next : cur->prev;

    return cur;
}

/* Deallocate the list iterator */

void ll_iter_free(LL_Iterator *self)
{
    if (self)
        free(self);
    self = NULL;
}

/* ---------------------------------------- */

/* LL */

/* Allocate a new LL struct and return it, or NULL on failure */

LL *ll_new(void)
{
    LL *self = malloc(sizeof(LL));

    if (!self)
        return NULL;

    self->head = NULL;
    self->tail = NULL;
    self->free = NULL;
    self->cmp = NULL;
    self->len = 0;

    return self;
}

/* Prepend the node `node` to the list `self` and return it, or NULL on failure */

LL_Node *ll_prepend(LL *self, LL_Node *node)
{
    if (!node)
        return NULL;

    if (self->len)
    {
        node->next = self->head;
        node->prev = NULL;
        self->head->prev = node;
        self->head = node;
    }
    else
    {
        self->head = self->tail = node;
        node->prev = node->next = NULL;
    }

    ++self->len;

    return node;
}

/* Append the node `node` to the list `self` and return it, or NULL on failure */

LL_Node *ll_append(LL *self, LL_Node *node)
{
    if (!node)
        return NULL;

    if (self->len == 0) /* list is empty */
    {
        self->head = self->tail = node;
        node->prev = node->next = NULL;
    }
    else
    {
        node->prev = self->tail;
        node->next = NULL;
        self->tail->next = self->tail = node;
    }

    ++self->len;

    return node;
}

/* Return/detach the first node in the list, or return NULL */

LL_Node *ll_shift(LL *self)
{
    if (self->len == 0)
        return NULL;

    LL_Node *first = self->head;

    if (--self->len)
        (self->head = first->next)->prev = NULL;
    else
        self->head = self->tail = NULL;

    first->next = first->prev = NULL;

    return first;
}

/* Return/detach the last node in the list, or return NULL */

LL_Node *ll_pop(LL *self)
{
    if (self->len == 0) /* no nodes... */
        return NULL;

    LL_Node *last = self->tail;

    if (--self->len)
        (self->tail = last->prev)->next = NULL;
    else /* len is 0 */
        self->tail = self->head = NULL;

    last->next = last->prev = NULL;

    return last;
}

/* Return the node associated to val, or NULL if not found */

LL_Node *ll_find(LL *self, void *val)
{
    LL_Iterator *it = ll_iter_new(self, LL_DIR_HEAD);
    LL_Node *node;

    while ((node = ll_iter_next(it)))
    {
        if (self->cmp)
        {
            if (self->cmp(val, node->val))
            {
                ll_iter_free(it);
                return node;
            }
        }
        else /* No custom compare function, just use C's == */
        {
            if (val == node->val)
            {
                ll_iter_free(it);
                return node;
            }
        }
    }

    ll_iter_free(it);

    /* If we got here, no node was found, so we return NULL */
    return NULL;
}

/* Return the node at the given index, or NULL if index is invalid */

LL_Node *ll_at(LL *self, int index)
{
    LL_Dir dir = LL_DIR_HEAD;

    if (index < 0) /* Negative index, search from the tail */
    {
        dir = LL_DIR_TAIL;
        index = ~index;
    }

    if ((unsigned int)index < self->len)
    {
        LL_Iterator *it = ll_iter_new(self, dir);
        LL_Node *node = ll_iter_next(it);
        while (index--)
            node = ll_iter_next(it);
        ll_iter_free(it);
        return node;
    }

    return NULL;
}

/*
 * Remove the given node from the list, freeing it and it's value.
 */

void ll_remove(LL *self, LL_Node *node)
{
    node->prev ? (node->prev->next = node->next) : (self->head = node->next);

    node->next ? (node->next->prev = node->prev) : (self->tail = node->prev);

    if (self->free)
        self->free(node->val);

    free(node);
    --self->len;
}

/* Deallocate the list */

void ll_free(LL *self)
{
    unsigned int len = self->len;
    LL_Node *next;
    LL_Node *cur = self->head;

    while (len--)
    {
        next = cur->next;
        if (self->free)
            self->free(cur->val);
        free(cur);
        cur = next;
    }

    free(self);
}

/* ---------------------------------------- */
