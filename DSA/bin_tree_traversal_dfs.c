#include <stdio.h>
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

int btree_dfs_traverse_preorder(BTNode* curr, int path[], int *idx);
int btree_dfs_traverse_inorder(BTNode* root, int path[], int *idx);
int btree_dfs_traverse_postorder(BTNode* root, int path[], int *idx);

int main()
{
    // initializing an empty binary tree of length 3;
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

// fill the tree with some sample data
/*
    7
   /  \
 23    3
 /\    /\
5  4 18  21

*/

    int arr_1[32] = {0};
    int arr_2[32] = {0};
    int arr_3[32] = {0};

    int idx_1 = 0;
    int idx_2 = 0;
    int idx_3 = 0;

    btree_dfs_traverse_preorder(root, arr_1, &idx_1);
    btree_dfs_traverse_inorder(root, arr_2, &idx_2);
    btree_dfs_traverse_postorder(root, arr_3, &idx_3);

    printf("btree preorder traversal: ");
    for (int i = 0; i < 7; i++)
    {
        printf("%i ,",arr_1[i]);
    }
    printf("\n");

    printf("btree inorder traversal: ");
    for (int i = 0; i < 7; i++)
    {
        printf("%i ,",arr_2[i]);
    }
    printf("\n");

    printf("btree postorder traversal: ");
    for (int i = 0; i < 7; i++)
    {
        printf("%i ,",arr_3[i]);
    }
    printf("\n");
    return 0;
}

int btree_dfs_traverse_preorder(BTNode* curr, int path[], int *idx)
{
    if (!curr)
    {
        return 0;
    }
    printf("DEBUG: IDX %i\n", *idx);

    //pre
    path[*idx] = curr->data;
    (*idx)++;

    //recurse
    btree_dfs_traverse_preorder(curr->left, path, idx);
    btree_dfs_traverse_preorder(curr->right, path, idx);

    //post
    return 0;
}

int btree_dfs_traverse_inorder(BTNode* curr, int path[], int *idx)
{
    if (!curr)
    {
        return 0;
    }
    printf("DEBUG: IDX %i\n", *idx);

    //pre

    //recurse
    btree_dfs_traverse_inorder(curr->left, path, idx);
    path[*idx] = curr->data;
    (*idx)++;
    btree_dfs_traverse_inorder(curr->right, path, idx);

    //post
    return 0;
}

int btree_dfs_traverse_postorder(BTNode* curr, int path[], int *idx)
{
    if (!curr)
    {
        return 0;
    }
    printf("DEBUG: IDX %i\n", *idx);

    //pre

    //recurse
    btree_dfs_traverse_postorder(curr->left, path, idx);
    btree_dfs_traverse_postorder(curr->right, path, idx);

    //post
    path[*idx] = curr->data;
    (*idx)++;
    return 0;
}
