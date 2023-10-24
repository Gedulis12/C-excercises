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

// Structs and function decalrations for queue
struct QNode {
    BTNode *value;
    struct QNode *next;
};

struct Queue {
    struct QNode *head;
    struct QNode *tail;
    int qlen;
};
//
// returns a pointer to the binary tree with root node set to NULL;
BTree* btree_create();

void btree_traversal_bfs(BTNode *root);

struct Queue* queue_create();
int queue_is_empty(struct Queue *queue);
BTNode* queue_peek(struct Queue *queue);
BTNode* queue_dequeue(struct Queue* queue);
BTNode* queue_enqueue(struct Queue *queue, BTNode* newval);
void free_queue(struct Queue *queue);

int main()
{
    // initializing ampty queue to store results in;
    struct Queue *queue = queue_create();

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

    btree_traversal_bfs(root);
    struct QNode *node = queue->head;
    int i = 1;
    while (node)
    {
        printf("queue item #%i: %i\n", i, node->value->data);
        node = node->next;
        i++;
    }
    return 0;
}

void btree_traversal_bfs(BTNode *root)
{
    struct Queue *fqueue = queue_create();
    queue_enqueue(fqueue, root);

    while (!queue_is_empty(fqueue))
    {
        BTNode* curr = queue_dequeue(fqueue);
        printf("%d ", curr->data);

        if (curr->left)
        {
            queue_enqueue(fqueue, curr->left);
        }

        if (curr->right)
        {
            queue_enqueue(fqueue, curr->right);
        }
    }
}


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

struct Queue* queue_create()
{
    struct Queue *queue = (struct Queue*)malloc(sizeof(struct Queue));
    if(!queue)
    {
        printf("Memory allocation failed for the queue.\n");
        return NULL;
    }
    queue->head = queue->tail = NULL;
    queue->qlen = 0;
    return queue;

}

int queue_is_empty(struct Queue *queue)
{
    return queue->qlen == 0;
}

BTNode* queue_peek(struct Queue *queue)
{
    if (queue_is_empty(queue))
    {
        printf("Queue is empty.\n");
        return NULL;
    }
    return queue->head->value;
}

BTNode* queue_dequeue(struct Queue* queue)
{
    if (queue_is_empty(queue))
    {
        printf("Queue is empty.\n");
        return NULL;
    }

    queue->qlen--;
    BTNode* value = queue->head->value;
    struct QNode *temp = queue->head;
    queue->head = temp->next;
    free(temp);
    return value;
}

BTNode* queue_enqueue(struct Queue *queue, BTNode* newval)
{
    struct QNode *node = (struct QNode*)malloc(sizeof(*node));
    if (!node)
    {
        printf("Memory allocation failed for a new node.\n");
        return NULL;
    }
    node -> value = newval;
    node->next = NULL;

    if (queue_is_empty(queue))
    {
        queue->head = queue->tail = node;
    }
    else
    {
        queue->tail->next = node;
        queue->tail = node;
    }
    queue->qlen++;

    return 0;
}

void free_queue(struct Queue *queue)
{
    while (!queue_is_empty(queue))
    {
        queue_dequeue(queue);
    }
    free(queue);
}
