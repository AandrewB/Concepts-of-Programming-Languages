#ifndef _BST_H_
#define _BST_H_

#include "shape.h"

typedef struct node_struct
{
  shape sh;
  struct node_struct* left;
  struct node_struct* right;
} node;

typedef struct bst_struct
{
  node* root;
} bst;

bst create_bst();

void insert_in_bst (bst* t, shape sh);

void inorder (bst t);

void free_bst (bst t);

#endif
