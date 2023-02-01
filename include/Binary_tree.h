#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__
#include "common.h"

// simple binary tree implementation with key value pairs

typedef struct BinTree {
  char *key;
  char *val;

  struct BinTree *left, *right;
} BinTree;

BinTree *binTree_init(char *key, char *val);
void binTree_inorder(BinTree *self);
BinTree *binTree_insert(BinTree *self, char *key, char *val);
char *binTree_search(BinTree *self, char *key);

#endif // __BINARY_TREE_H__