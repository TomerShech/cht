#include "list.h"

/* -------------------------------------- */

/* Allocate a new list_node struct with value `val` and return it, or NULL on failure */

list_node *list_node_new(void *val)
{
    list_node *this = malloc(sizeof(list_node));

    if (!this)
        return NULL;

    this->prev = NULL;
    this->next = NULL;
    this->val = val;

    return this;
}

/* -------------------------------------- */

/* Allocate a new list_iterator struct from list `list` and direction `dir`. Return it, or NULL on failure */

list_iterator *list_iter_new(list *list, list_dir dir)
{
    list_node *node = dir == LIST_DIR_HEAD ? list->head : list->tail;
    return list_iter_new_from_node(node, dir);
}

/* Allocate a new list_iterator with list node `node`. Return it, or NULL on failure */

list_iterator *list_iter_new_from_node(list_node *node, list_dir dir)
{
    list_iterator *this = malloc(sizeof(list_iterator));

    if (!this)
        return NULL;

    this->next = node;
    this->dir = dir;

    return this;
}

/* Return the next list node or NULL when no more nodes are left in the list */

list_node *list_iter_next(list_iterator *this)
{
    list_node *cur = this->next;

    if (cur)
        this->next = this->dir == LIST_DIR_HEAD ? cur->next : cur->prev;

    return cur;
}

/* Deallocate list iterator `this` */

void list_iter_free(list_iterator *this)
{
    free(this);
    this = NULL;
}

/* -------------------------------------- */

/* Allocate a new list struct and return it, or NULL on failure */

list *list_new(void)
{
    list *this = malloc(sizeof(list));

    if (!this)
        return NULL;

    this->head = NULL;
    this->tail = NULL;
    this->free = NULL;
    this->cmp = NULL;
    this->len = 0;

    return this;
}

/* Prepend node `node` to list `this` and return it, or NULL on failure */

list_node *list_prepend(list *this, list_node *node)
{
    if (!node)
        return NULL;

    if (this->len == 0)
    {
        this->head = this->tail = node;
        node->prev = node->next = NULL;
    }
    else
    {
        node->next = this->head;
        node->prev = NULL;
        this->head->prev = node;
        this->head = node;
    }

    ++this->len;

    return node;
}

/* Append node `node` to list `this` and return it, or NULL on failure */

list_node *list_append(list *this, list_node *node)
{
    if (!node)
        return NULL;

    if (this->len == 0)
    {
        this->head = this->tail = node;
        node->prev = node->next = NULL;
    }
    else
    {
        node->prev = this->tail;
        node->next = NULL;
        this->tail->next = node;
        this->tail = node;
    }

    ++this->len;

    return node;
}

/* Return/detach the first node in list `this`, or return NULL */

list_node *list_shift(list *this)
{
    if (!this->len)
        return NULL;

    list_node *node = this->head;

    if (--this->len)
        (this->head = node->next)->prev = NULL;
    else
        this->head = this->tail = NULL;

    node->next = node->prev = NULL;

    return node;
}

/* Return/detach the last node in list `this`, or return NULL */

list_node *list_pop(list *this)
{
    if (!this->len)
        return NULL;

    list_node *node = this->tail;

    if (--this->len)
        (this->tail = node->prev)->next = NULL;
    else
        this->tail = this->head = NULL;

    node->next = node->prev = NULL;

    return node;
}

/* Return the node associated to value `val`, or NULL if not found */

list_node *list_find(list *this, void *val)
{
    list_iterator *it = list_iter_new(this, LIST_DIR_HEAD);
    list_node *node;

    while ((node = list_iter_next(it)))
    {
        if (this->cmp)
        {
            if (this->cmp(val, node->val))
            {
                list_iter_free(it);
                return node;
            }
        }
        else /* No custom compare function, just use C's == */
        {
            if (val == node->val)
            {
                list_iter_free(it);
                return node;
            }
        }
    }

    list_iter_free(it);

    /* If we got here, no node was found, so we return NULL */
    return NULL;
}

/* Return the node at index `i`, or NULL if i is invalid */

list_node *list_at(list *this, int i)
{
    list_dir dir = LIST_DIR_HEAD;

    if (i < 0)
    {
        dir = LIST_DIR_TAIL;
        i = ~i;
    }

    if ((unsigned int)i < this->len)
    {
        list_iterator *it = list_iter_new(this, dir);
        list_node *node = list_iter_next(it);
        while (i--)
            node = list_iter_next(it);
        list_iter_free(it);
        return node;
    }

    return NULL;
}

/* Remove node `node` from list `this`, deallocate it and its value `val` */

void list_remove(list *this, list_node *node)
{
    node->prev ? (node->prev->next = node->next) : (this->head = node->next);
    node->next ? (node->next->prev = node->prev) : (this->tail = node->prev);

    if (this->free)
        this->free(node->val);

    free(node);

    --this->len;
}

/*
 * Reverse list `this` in place.
 * E.g. list ["a" => "b" => "c" => NULL] becomes ["c" => "b" => "a" => NULL]
 */

void list_reverse(list *this)
{
    list_iterator *it = list_iter_new(this, LIST_DIR_HEAD);
    list_node *tmp = this->head;
    list_node *cur;

    this->head = this->tail;
    this->tail = tmp;

    while ((cur = list_iter_next(it)))
    {
        tmp = cur->next;
        cur->next = cur->prev;
        cur->prev = tmp;
    }

    list_iter_free(it);
}

/* Deallocate all nodes of list `this`, as well as the list itself */

void list_free(list *this)
{
    unsigned int len = this->len;
    list_node *next;
    list_node *cur = this->head;

    while (len--)
    {
        next = cur->next;
        if (this->free)
            this->free(cur->val);
        free(cur);
        cur = next;
    }

    free(this);
}

/* -------------------------------------- */
