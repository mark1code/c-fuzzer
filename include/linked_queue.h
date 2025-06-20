#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 1024

typedef struct Node {
    char input[INPUT_SIZE];
    struct Node *next;
} Node;

typedef struct Queue {
    Node *head;
    Node *tail;
} Queue;

Queue* queue_create(void);
void queue_destroy(Queue *q);

int enqueue(Queue *q, const char *input);
char* dequeue (Queue *q);

#endif // LINKED_QUEUE_H
