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

bool bst_search(BTNode *node, int needle);


int main()
{
/* initializing an empty binary tree of length 3;
    14
   /  \
 10    21
 /\    /\
8  11 17 30
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

    root->data = 14;
    left_1->data = 10;
    left_2->data = 8;
    left_1_right_2->data = 11;

    right_1->data = 21;
    right_2->data = 30;
    right_1_left_2->data = 17;

    bool res1 = bst_search(root, 20); // expecting False
    bool res2 = bst_search(root, 11); // expecting True

    printf("results of searching BST for value 20 (expecting to get not found), %s\n", res1 ? "found" : "not found");

    printf("results of searching BST for value 11 (expecting to get found), %s\n", res2 ? "found" : "not found");

    return 0;
}


bool bst_search(BTNode *node, int needle)
{
    if (!node)
    {
        return false; // node doesn't exist
    }
    printf("DEBUG: %i\n", node->data);

    if (node->data == needle)
    {
        return true; // we found the value
    }

    if(node->data < needle)
    {
        bst_search(node->right, needle); // nodes value is less than what we look for, hence we need to move to the right side
    }
    else if (node->data > needle)
    {
        bst_search(node->left, needle); // nodes value is more than what we look for, hence we need to move to the left side
    }
    else
    {
        return false;
    }
}
