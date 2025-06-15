#include <stdio.h>
#include "linked_queue.h"

Queue* queue_create(void) {
    Queue *q = malloc(sizeof(Queue));
    if(q){
        q->tail = NULL;
        q->head = q->tail;
    }
    return q;
}

void queue_destroy(Queue *q) {
    while(q->head != NULL) {
        Node* temp = q->head;
        q->head = q->head->next;
        free(temp);
    }
    free(q);
}

int enqueue(Queue *q, const char *input) {
    Node *new_node = malloc(sizeof(Node));
    if(!new_node) return -1;
    strncpy(new_node->input, input, SIZE_INPUT - 1);
    new_node->input[SIZE_INPUT - 1] = '\0';
    new_node->next = NULL;

    if(q->tail == NULL) {
        q->head = new_node; 
        q->tail = new_node;
    }
    else {
        q->tail->next = new_node;
        q->tail= new_node;
    }
    return 0;
}

char* dequeue(Queue *q) {
    if(q->head == NULL) return NULL;
    Node *node_dequeued = q->head;
    char *input_copy = strdup(node_dequeued->input);
    if(!input_copy) return NULL;

    q->head = q->head->next;
    if(q->head == NULL) q->tail = NULL;
    free(node_dequeued);
    return input_copy;
}

