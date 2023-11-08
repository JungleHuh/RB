#ifndef _HELPER_H_
#define _HELPER_H_

#include "rbtree.h"

void printPreOrder(rbtree *);
void preOrder(rbtree *,node_t *);
void postOrderDelete(rbtree *, node_t *);

void rbtree_fixup(rbtree *, node_t *);
void right_rotate(rbtree *, node_t *);
void left_rotate(rbtree *, node_t *);

void rb_transplant(rbtree *, node_t *, node_t *);
node_t* rbtree_minimum(const rbtree *, node_t *);
void rb_erase_fixup(rbtree *, node_t *);
void inOrderToArray(const rbtree *, node_t *, key_t *, size_t, int *);

#endif //_HELPER_H_