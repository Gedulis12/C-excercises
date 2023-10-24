# include "queue.h"

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

int queue_peek(struct Queue *queue)
{
    if (queue_is_empty(queue))
    {
        printf("Queue is empty.\n");
        return -1;
    }
    return queue->head->value;
}

int queue_dequeue(struct Queue* queue)
{
    if (queue_is_empty(queue))
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
