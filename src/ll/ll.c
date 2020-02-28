#include <stdlib.h>

#include "ll.h"

/* LL_Node */

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

/* LL_Iterator */

LL_Iterator *ll_iter_new(LL *list, LL_Dir dir)
{
    LL_Node *node = dir == LL_DIR_HEAD ? list->head : list->tail;
    return ll_iter_new_from_node(node, dir);
}

/*
 * Allocate a new LL_Iterator with the given start
 * node. NULL on failure.
 */

LL_Iterator *ll_iter_new_from_node(LL_Node *node, LL_Dir dir)
{
    LL_Iterator *self = malloc(sizeof(LL_Iterator));

    if (!self)
        return NULL;

    self->next = node;
    self->dir = dir;

    return self;
}

/*
 * Return the next LL_Node or NULL when no more
 * nodes remain in the list.
 */

LL_Node *ll_iter_next(LL_Iterator *self)
{
    LL_Node *curr = self->next;

    if (curr)
        self->next = self->dir == LL_DIR_HEAD ? curr->next : curr->prev;

    return curr;
}

/*
 * Free the list iterator.
 */

void ll_iter_free(LL_Iterator *self)
{
    free(self);
    self = NULL;
}

/* LL */

/*
 * Allocate a new LL. NULL on failure.
 */

LL *ll_new(void)
{
    LL *self = malloc(sizeof(LL));
    if (!self)
        return NULL;

    self->head = NULL;
    self->tail = NULL;
    self->free = NULL;
    self->match = NULL;
    self->len = 0;

    return self;
}

/*
 * Free the list.
 */

void ll_free(LL *self)
{
    unsigned int len = self->len;
    LL_Node *next;
    LL_Node *curr = self->head;

    while (len--)
    {
        next = curr->next;
        if (self->free)
            self->free(curr->val);
        free(curr);
        curr = next;
    }

    free(self);
}

/*
 * Append the given node to the list
 * and return the node, NULL on failure.
 */

LL_Node *ll_rpush(LL *self, LL_Node *node)
{
    if (!node)
        return NULL;

    if (self->len == 0)
    {
        self->head = node;
        self->tail = node;
        node->prev = NULL;
        node->next = NULL;
    }
    else
    {
        node->prev = self->tail;
        node->next = NULL;
        self->tail->next = node;
        self->tail = node;
    }

    ++self->len;

    return node;
}

/*
 * Return / detach the last node in the list, or NULL.
 */

LL_Node *ll_rpop(LL *self)
{
    if (self->len == 0)
        return NULL;

    LL_Node *node = self->tail;

    if (--self->len)
        (self->tail = node->prev)->next = NULL;
    else
        self->tail = self->head = NULL;

    node->next = node->prev = NULL;

    return node;
}

/*
 * Return / detach the first node in the list, or NULL.
 */

LL_Node *ll_lpop(LL *self)
{
    if (self->len == 0)
        return NULL;

    LL_Node *node = self->head;

    if (--self->len)
        (self->head = node->next)->prev = NULL;
    else
        self->head = self->tail = NULL;

    node->next = node->prev = NULL;

    return node;
}

/*
 * Prepend the given node to the list
 * and return the node, NULL on failure.
 */

LL_Node *ll_lpush(LL *self, LL_Node *node)
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

/*
 * Return the node associated to val or NULL.
 */

LL_Node *ll_find(LL *self, void *val)
{
    LL_Iterator *it = ll_iter_new(self, LL_DIR_HEAD);
    LL_Node *node;

    while ((node = ll_iter_next(it)))
    {
        if (self->match)
        {
            if (self->match(val, node->val))
            {
                ll_iter_free(it);
                return node;
            }
        }
        else
        {
            if (val == node->val)
            {
                ll_iter_free(it);
                return node;
            }
        }
    }

    ll_iter_free(it);

    return NULL;
}

/*
 * Return the node at the given index or NULL.
 */

LL_Node *ll_at(LL *self, int index)
{
    LL_Dir dir = LL_DIR_HEAD;

    if (index < 0)
    {
        dir = LL_DIR_TAIL;
        index = ~index;
    }

    if ((unsigned)index < self->len)
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
