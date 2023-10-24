#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// structs for the binary tree nodes and the tree itself
typedef struct BTNode {
    int data;
    struct BTNode *left;
    struct BTNode *right;
} BTNode;

typedef struct {
    BTNode *root;
} BTree;

// returns a pointer to the binary tree with root node set to NULL;
BTree* btree_create()
{
    BTree *btree  =(BTree*)malloc(sizeof(BTree));
    if (!btree)
    {
        printf("Memory allocation failed for the tree.\n");
        return NULL;
    }
    btree->root = NULL;
    return btree;
}

bool compare(BTNode *a, BTNode *b);

int main()
{
/* initializing an empty binary tree of length 3;
    7
   /  \
 23    3
 /\    /\
5  4 18  21
*/

    // tree a
    BTree *btree = btree_create();

    BTNode *root = (BTNode*)malloc(sizeof(BTNode));
    root->left = NULL;
    root->right = NULL;
    btree->root = root;

    BTNode *left_1 = (BTNode*)malloc(sizeof(BTNode));
    BTNode *left_2 = (BTNode*)malloc(sizeof(BTNode));
    BTNode *left_1_right_2 = (BTNode*)malloc(sizeof(BTNode));
    BTNode *right_1 = (BTNode*)malloc(sizeof(BTNode));
    BTNode *right_2 = (BTNode*)malloc(sizeof(BTNode));
    BTNode *right_1_left_2 = (BTNode*)malloc(sizeof(BTNode));

    root->data = 7;
    left_1->data = 23;
    left_2->data = 5;
    left_1_right_2->data = 4;

    right_1->data = 3;
    right_2->data = 21;
    right_1_left_2->data = 18;

    root->left = left_1;
    root->right = right_1;

    left_1->left = left_2;
    left_1->right = left_1_right_2;

    right_1->left = right_1_left_2;
    right_1->right = right_2;

    left_2->left = NULL;
    left_2->right = NULL;

    right_2->left = NULL;
    right_2->right = NULL;

    left_1_right_2->left = NULL;
    left_1_right_2->right = NULL;

    right_1_left_2->left = NULL;
    right_1_left_2->right = NULL;

    root->data = 7;
    left_1->data = 23;
    left_2->data = 5;
    left_1_right_2->data = 4;
    right_1->data = 3;
    right_1_left_2->data = 18;
    right_2->data = 21;

    // tree b
    BTree *btreeb = btree_create();

    BTNode *rootb = (BTNode*)malloc(sizeof(BTNode));
    rootb->left = NULL;
    rootb->right = NULL;
    btreeb->root = rootb;

    BTNode *left_1b = (BTNode*)malloc(sizeof(BTNode));
    BTNode *left_2b = (BTNode*)malloc(sizeof(BTNode));
    BTNode *left_1_right_2b = (BTNode*)malloc(sizeof(BTNode));
    BTNode *right_1b = (BTNode*)malloc(sizeof(BTNode));
    BTNode *right_2b = (BTNode*)malloc(sizeof(BTNode));
    BTNode *right_1_left_2b = (BTNode*)malloc(sizeof(BTNode));

    rootb->data = 7;
    left_1b->data = 23;
    left_2b->data = 5;
    left_1_right_2b->data = 4;

    right_1b->data = 3;
    right_2b->data = 21;
    right_1_left_2b->data = 18;

    rootb->left = left_1;
    rootb->right = right_1;

    left_1b->left = left_2;
    left_1b->right = left_1_right_2;

    right_1b->left = right_1_left_2;
    right_1b->right = right_2;

    left_2b->left = NULL;
    left_2b->right = NULL;

    right_2b->left = NULL;
    right_2b->right = NULL;

    left_1_right_2b->left = NULL;
    left_1_right_2b->right = NULL;

    right_1_left_2b->left = NULL;
    right_1_left_2b->right = NULL;

    rootb->data = 1;
    left_1b->data = 2;
    left_2b->data = 3;
    left_1_right_2b->data = 4;
    right_1b->data = 5;
    right_1_left_2b->data = 6;
    right_2b->data = 7;

    // tree c
    BTNode *rootc = root;

    bool res1 = compare(root, rootb); // expecting False
    bool res2 = compare(root, rootc); // expecting True

    printf("results of caparing tree a to tree b (expecting to get false), %s\n", res1 ? "true" : "false");

    printf("results of caparing tree a to tree c (expecting to get true), %s\n", res2 ? "true" : "false");

    return 0;
}


bool compare(BTNode *a, BTNode *b)
{

    if (a == NULL && b == NULL)
    {
        return true;
    }

    if (a == NULL || b == NULL)
    {
        return false;
    }

    if (a->data != b->data)
    {
        return false;
    }
    bool res_a = compare(a->left, b->left);
    bool res_b = compare(a->right, b->right);
    if (res_a && res_b)
    {
        return true;
    }
    else
    {
        return false;
    }
}
