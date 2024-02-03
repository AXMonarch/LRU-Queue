#ifndef LL_QUEUE_H
#define LL_QUEUE_H

#include <stdbool.h>

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    Node *tail;
    int size;
    int maxSize;
} Queue;

// Function Prototypes
Queue *create_queue(int maxSize);
int size(Queue *queue);
bool is_empty(Queue *queue);
void peek(Queue *queue);
void enqueue(Queue *queue, int value);
int dequeue(Queue *queue);
void erase_node(Queue *queue, int value);
void destroy_queue(Queue *queue);
void print_queue(Queue *queue);

#endif /* LL_QUEUE_H */
