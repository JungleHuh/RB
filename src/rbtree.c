#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rbtree.h"
#include "helper.h"

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil = (node_t *)calloc(1, sizeof(node_t));
  node_t nilNode = {RBTREE_BLACK, -1,0,0,0,};
  *nil = nilNode;

  p ->nil = nil;
  p ->root = nil;
  return p;
}

void printPreOrder(rbtree *tree)
{
  printf("프린트 시작\n");
  preOrder(tree, tree -> root);
}

void preOrder(rbtree *tree, node_t *nowNode)
{
  if(nowNode == tree -> nil)
    return;

  char * color;
  if (nowNode -> color = RBTREE_RED)
  {
    color = "R";
  }
  else
  {
    color = "B";
  }
  char *leftColor = nowNode->left->color == RBTREE_BLACK ? "B":"R";
  char *rightColor = nowNode->right->color == RBTREE_BLACK ? "B":"R";

  char leftKey[10] = "o";
  char rightKey[10] = "o";
  if (nowNode -> left !=tree->nil) sprintf(leftKey, "%d", nowNode->left->key);
  if (nowNode -> right !=tree->nil) sprintf(rightKey,"%d", nowNode->right->key);
  printf("%s(%s)/%d(%s)\\%s(%s)\n", leftKey, leftColor, nowNode->key, color, rightKey, rightColor);
  preOrder(tree, nowNode->left);
  preOrder(tree, nowNode->right);
  return;
}

void rbtree_insert_fixup(rbtree *t, const key_t key){
  node_t node = {RBTREE_RED, key, t->nil, t->nil, t->nil};
  node_t *newNode = (node_t *)calloc(1, sizeof(node_t));

  *newNode = node;

  node_t *x = t->root;
  node_t *y = x;

  if(t->root == t->nil){
    t->root = newNode;
    newNode -> color = RBTREE_BLACK;
  }else{
    while( x != t->nil){
      y = x;
      if(key < x->key){
        x = x->left;
      }else{
        x = x->right;
      }
    }
    if(key < y->key){
      y->left = newNode;
    }else{
      y->right = newNode;
    }
    newNode->parent = y;

    if(y->color == RBTREE_RED){
      rbtree_fixup(t, newNode);
    }
  }
  return newNode;
}

void rbtree_fixup(rbtree *t, node_t *n){
  while(n->parent->color == RBTREE_RED){
    if(n->parent == n->parent->parent->left){
      node_t *uncle = n->parent->parent->right;
      if(uncle->color == RBTREE_RED){
        uncle->color = RBTREE_BLACK;
        n->parent->color = RBTREE_BLACK;
        n->parent->parent->color = RBTREE_RED;
        n = n->parent->parent;
      }else{
        if(n == n->parent->right){
          n = n->parent;
          left_rotate(t,n);
        }
        n ->parent->color =RBTREE_BLACK;
        n ->parent->parent->color == RBTREE_RED;
        right_rotate(t,n);
      }
      
      }else{
        node_t *uncle = n->parent->parent->left;
        if(uncle->color == RBTREE_RED){
        uncle->color = RBTREE_BLACK;
        n->parent->color = RBTREE_BLACK;
        n->parent->parent->color = RBTREE_RED;
        n = n->parent->parent;
      }else{
        if(n == n->parent->left){
          n = n->parent;
          right_rotate(t,n);
        }
        n ->parent->color =RBTREE_BLACK;
        n ->parent->parent->color == RBTREE_RED;
        left_rotate(t,n);
      }
      }
    }
       t->root->color = RBTREE_BLACK;
  }

  void left_rotate(rbtree *t, node_t * x)
{
  node_t *y = x -> right;

  x->right = y -> left;
  if( y -> left != t->nil)
{
  y -> left -> parent = x;
}  
  y -> parent = x -> parent;

  if( x-> parent == t ->nil)
  {
    t->root = y;
  }
  else if( x == x->parent->left)
{
  x ->parent->left = y;
}
 else 
 {
  x -> parent ->right = y;
 }
  y->left = x;
  // x의 부모 노드를 y로 변경
  x->parent = y;

}

void right_rotate(rbtree *t, node_t *y)
{
  //x가 저장되는 위치 선언
  node_t *x = y ->left;

  y -> left = x -> right;
  if( x->right != t->nil)
  {
    x-> right ->parent = y;
  }
  x->parent = y->parent;

  if( y-> parent == t ->nil)
  {
    t ->root = x;
  }
  else if (y == y->parent->right)
  {
    y->parent->right = x;
  }
  else
  {
    y->parent->left = x;
  }

  // y를 x의 오른쪽 자식 노드로 변경
  x->right = y;
  // y의 부모 노드를 x로 변경
  y->parent = x;
}

node_t *rbtree_find(const rbtree *t, const key_t key){

  node_t *n = t->root;
  while(n !=t->nil && n->key != key){
    if(key < n->key){
      n = n->left;
    }else{
      n = n->right;
    }
  }
  return n == t->nil?0:n;
}

node_t *rbtree_min(const rbtree *t){
  return rbtree_minimum(t, t->root);
}

node_t *rbtree_max(const rbtree *t){
  node_t *x = t->root;
  while(x->right != t->nil){
    x = x->right;
  }
  return x;
}

node_t * rbtree_minimum(const rbtree *t, node_t *x){
  while(x->left!=t->nil){
    x = x->left;
  }
  return x;
}
//Delete가 호출하는 서브 루틴인 transpalnt를 먼저 적용해야 함.
void rb_transplant(rbtree *tree, node_t *u, node_t *v){
  assert(u != tree->nil);
  if(u->parent == tree->nil){
     tree->root =v;
  }else if(u->parent->left = v){
  }else{
    u->parent->right = v;
  }
 v->parent = u->parent;
}

void delete_rbtree(rbtree *t) {
  postOrderDelete(t, t->root);
  free(t);
  printf("\n삭제 완료\n");
}

void postOrderDelete(rbtree *t, node_t *n)
{
  if(n == t->nil) return;
  postOrderDelete(t, n->left);
  postOrderDelete(t, n->right);
  printf("(%d 삭제)", n->key);
  rbtree_erase(t, n);
}

int rbtree_erase(rbtree *t, node_t *p) {
  node_t *x;
  node_t *y = p;
  color_t y_original_color = y ->color;

  if (p->left == t->nil){
    x = p->right;
    rb_transplant(t,p,p->left);
  }else if(p->right == t->nil){
    x = p->left;
    rb_transplant(t,p,p->left);
  }else{
    y = rbtree_minimum(t, p->right);
    y_original_color = y ->color;
    x = y->right;
    if(y->parent == p){
      x->parent = y;
    }else{
      rb_transplant(t,y,y->right);
      y->right = p->left;
      y->left->parent = y;
      y->color = p->color;
    }
    free(p);
    p=NULL;

    if (y_original_color == RBTREE_BLACK){
      rb_erase_fixup(t,x);
    }

  }
  t->nil->parent = NULL;
  t->nil->right = NULL;
  t->nil->left = NULL;
  t->nil->color = RBTREE_BLACK;
  
  return 0;
}

void rb_erase_fixup(rbtree *tree, node_t *x){



}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}