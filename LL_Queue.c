#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "LL_Queue.h"

int main(void)
{
    Queue *Q = create_queue(4);
    enqueue(Q,1);
    enqueue(Q,2);
    enqueue(Q,3);
    enqueue(Q,4);
    enqueue(Q,5);
    print_queue(Q);
    destroy_queue(Q);
    return 0;
}

Queue *create_queue(int maxSize)
{
    if (maxSize <= 0)
    {
        printf("Error: Maximum size must be greater than 0\n");
        return NULL;
    }

    Queue *queue = malloc(sizeof(Queue));
    
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    queue->maxSize = maxSize;

    return queue;
}

int size(Queue *queue)
{
    return queue->size;
}

bool is_empty(Queue *queue)
{
    return (size(queue) == 0);
}

void peek(Queue *queue)
{
    if (is_empty(queue))
    {
        printf("The Queue is Empty!\n");
    }
    else
    {
        printf("%d is the head.\n", queue->head->value);
    }
}

void enqueue(Queue *queue, int value)
{
    if (size(queue) >= queue->maxSize) // LRU EVICTION POLICY
    {
        Node *current = queue->head;
        while (current != NULL && current->value != value)
        {
            current = current->next;
        }

        if (current == NULL)
        {
            dequeue(queue);
            enqueue(queue, value);
            return;
        }

        erase_node(queue,value);
        enqueue(queue, value);
        return;
    }

    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Error: Memory allocation failed\n");
        return;
    }

    newNode->value = value;
    newNode->next = NULL;

    if (is_empty(queue))
    {
        queue->head = newNode;
        queue->tail = newNode;
    }
    else
    {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }

    queue->size++;
}

int dequeue(Queue *queue)
{
    if (is_empty(queue))
    {
        return -1;
    }

    int value = queue->head->value;
    Node *oldHead = queue->head;

    if (queue->size == 1)
    {
        queue->head = NULL;
        queue->tail = NULL;
    }

    else
    {
        queue->head = queue->head->next;
    }

    free(oldHead);
    queue->size--;
}

void erase_node(Queue *queue, int value)
{
    if (is_empty(queue))
    {
        return;
    }

    Node *current = queue->head;
    Node *prev = NULL;

    while (current != NULL && current->value != value)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        return;
    }

    // FIRST NODE REMOVAL
    if (prev == NULL)
    {
        queue->head = current->next;
        if (queue->head == NULL)
        {
            // If the list becomes empty, update the tail
            queue->tail = NULL;
        }
    }
    else // ANY NODE REMOVED
    {
        // SKIP THE CURRENT NODE
        prev->next = current->next;

        // REMOVE TAIL NODE
        if (current == queue->tail)
        {
            queue->tail = prev;
        }
    }

    free(current);
    queue->size--;
}

void print_queue(Queue *queue)
{
    if (is_empty(queue))
    {
        printf("Queue is empty.\n");
        return;
    }

    Node *current_node = queue->head;

    while (current_node != NULL)
    {
        printf("%d", current_node->value);
        printf("->");
        current_node = current_node->next;
    }
}

void destroy_queue(Queue *queue)
{
    Node *current_node = queue->head;
    while (current_node != NULL)
    {
        Node *temp = current_node;
        current_node = current_node->next;
        free(temp);
    }

    free(queue);
}