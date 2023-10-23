#include <stdio.h>
#include <stdlib.h>

struct SNode {
    int value;
    struct SNode *prev;
};

struct Stack {
    struct SNode *head;
};

struct Stack* create_stack()
{

    struct Stack *stack = (struct Stack*)malloc(sizeof(struct Stack));
    if(!stack)
    {
        printf("Memory allocation failed for the stack.\n");
        return NULL;
    }
    stack->head = stack->head = NULL;
    return stack;
}

int stack_peek(struct Stack *stack)
{
    if (stack->head)
    {
        return stack->head->value;
    }
    return -1; // stack is empty
}

int stack_push(struct Stack *stack, int newval)
{
    struct SNode *node = (struct SNode*)malloc(sizeof(*node));
    if (!node)
    {
        printf("Memory allocation failed for a new node.\n");
        return -1;
    }

    node->value = newval;
    node->prev = stack->head;
    stack->head = node;

    return 0;
}

int stack_pop(struct Stack *stack)
{
    if (stack->head == NULL)
    {
        return -1; // stack is empty
    }

    int value = stack->head->value;
    struct SNode *temp = stack->head;
    stack->head = stack->head->prev;
    free(temp);

    return value;
}

void free_stack(struct Stack *stack)
{
    while (stack->head != NULL)
    {
        stack_pop(stack);
    }
    free(stack);
}

int main()
{

    struct Stack *stack = create_stack();
    stack_push(stack, 5);
    printf("peeking: %i\n", stack_peek(stack));
    stack_push(stack, 6);
    printf("peeking: %i\n", stack_peek(stack));
    stack_push(stack, 7);
    printf("peeking: %i\n", stack_peek(stack));
    stack_push(stack, 7);
    printf("peeking: %i\n", stack_peek(stack));
    stack_pop(stack);
    printf("peeking: %i\n", stack_peek(stack));
    stack_pop(stack);
    printf("peeking: %i\n", stack_peek(stack));
    stack_pop(stack);
    printf("peeking: %i\n", stack_peek(stack));
    stack_pop(stack);
    printf("peeking: %i\n", stack_peek(stack));
    stack_pop(stack);
    printf("peeking: %i\n", stack_peek(stack));
}

