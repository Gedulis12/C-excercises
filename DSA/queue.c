#include <stdio.h>
#include <stdlib.h>

struct QNode {
    int value;
    struct QNode *next;
};

struct Queue {
    struct QNode *head;
    struct QNode *tail;
    int qlen;
};


struct Queue* create_queue()
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

int is_empty(struct Queue *queue)
{
    return queue->qlen == 0;
}

int queue_peek(struct Queue *queue)
{
    if (is_empty(queue))
    {
        printf("Queue is empty.\n");
        return -1;
    }
    return queue->head->value;
}

int queue_dequeue(struct Queue* queue)
{
    if (is_empty(queue))
    {
        printf("Queue is empty.\n");
        return -1;
    }

    queue->qlen--;
    int value = queue->head->value;
    struct QNode *temp = queue->head;
    queue->head = temp->next;
    free(temp);
    return value;
}

int queue_enqueue(struct Queue *queue, int newval)
{
    struct QNode *node = (struct QNode*)malloc(sizeof(*node));
    if (!node)
    {
        printf("Memory allocation failed for a new node.\n");
        return -1;
    }
    node -> value = newval;
    node->next = NULL;

    if (is_empty(queue))
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
    while (!is_empty(queue))
    {
        queue_dequeue(queue);
    }
    free(queue);
}

int main()
{

    struct Queue *queue = create_queue();
    queue_enqueue(queue, 5);
    printf("peeking: %i\n", queue_peek(queue));
    queue_enqueue(queue, 6);
    printf("peeking: %i\n", queue_peek(queue));
    queue_enqueue(queue, 7);
    printf("peeking: %i\n", queue_peek(queue));
    queue_dequeue(queue);
    printf("peeking: %i\n", queue_peek(queue));
    queue_dequeue(queue);
    printf("peeking: %i\n", queue_peek(queue));
    queue_dequeue(queue);
    printf("peeking: %i\n", queue_peek(queue));
    queue_dequeue(queue);
    printf("peeking: %i\n", queue_peek(queue));
}

