#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *l = malloc(sizeof(struct list_head));
    if (l)
        INIT_LIST_HEAD(l);
    return l;
}

/* Free all storage used by queue */
void q_free(struct list_head *l)
{
    if (!l)
        return;
    element_t *il, *tmp;
    list_for_each_entry_safe (il, tmp, l, list)
        q_release_element(il);
    free(l);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *q = malloc(sizeof(element_t));
    if (!q) {
        free(q);
        return false;
    }
    int len = strlen(s) + 1;
    q->value = malloc(sizeof(char) * len);
    if (!(q->value)) {
        free(q);
        return false;
    }
    strncpy(q->value, s, len);
    list_add(&q->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *q = malloc(sizeof(element_t));
    if (!q) {
        free(q);
        return false;
    }
    int len = strlen(s) + 1;
    q->value = malloc(sizeof(char) * len);
    if (!(q->value)) {
        free(q);
        return false;
    }
    strncpy(q->value, s, len);
    list_add_tail(&q->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *t = list_first_entry(head, element_t, list);

    list_del_init(head->next);
    if (sp) {
        strncpy(sp, t->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    return t;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *t = list_entry(head->prev, element_t, list);

    list_del_init(head->prev);
    if (sp) {
        strncpy(sp, t->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    return t;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;
    int len = 0;
    struct list_head *li;
    list_for_each (li, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (!head || list_empty(head))
        return NULL;
    int len = q_size(head);
    int mid = (len % 2) ? len / 2 + 1 : len / 2;
    element_t *t;
    list_for_each_entry (t, head, list) {
        if (--mid == 0) {
            list_del(&t->list);
            free(t->value);
            free(t);
            break;
        }
    }
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending order */
void q_sort(struct list_head *head) {}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending order */
int q_merge(struct list_head *head)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
