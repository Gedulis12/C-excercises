#include <stdio.h>
#include <stdlib.h>

#ifndef QUEUE
#define QUEUE


struct QNode {
    int value;
    struct QNode *next;
};

struct Queue {
    struct QNode *head;
    struct QNode *tail;
    int qlen;
};

struct Queue* queue_create();
int queue_is_empty(struct Queue *queue);
int queue_peek(struct Queue *queue);
int queue_dequeue(struct Queue* queue);
int queue_enqueue(struct Queue *queue, int newval);
void free_queue(struct Queue *queue);

#endif
