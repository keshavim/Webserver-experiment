#include "Binary_tree.h"

BinTree *binTree_init(char *key, char *val)
{
    BinTree *temp = (BinTree *)malloc(sizeof(BinTree));
    temp->key = key;
    temp->val = val;

    temp->left = temp->right = NULL;
    return temp;
}

// prints out tree
void binTree_inorder(BinTree *self)
{
    if (self != NULL)
    {
        binTree_inorder(self->left);
        printf("\nkey:%s | val:%s\n", self->key, self->val);
        binTree_inorder(self->right);
    }
}

// recrsively moves through the tree until at NULL node
BinTree *binTree_insert(BinTree *self, char *key, char *val)
{
    if (self == NULL)
    {
        return binTree_init(key, val);
    }

    int32_t cmp = strcmp(key, self->key);
    if (cmp == 0)
    {
        printf("key exits: %s\n", key);
    }
    else if (cmp > 0)
    {
        self->right = binTree_insert(self->right, key, val);
    }
    else
    {
        self->left = binTree_insert(self->left, key, val);
    }
    return self;
}

char *binTree_search(BinTree *self, char *key)
{
    if (self == NULL)
    {
        return "error.html";
    }

    if (strcmp(key, self->key) == 0)
    {
        return self->val;
    }
    else if (strcmp(key, self->key) > 0)
    {
        return binTree_search(self->right, key);
    }
    else if (strcmp(key, self->key) < 0)
    {
        return binTree_search(self->left, key);
    }
}