#include <stdio.h>
#include <unistd.h>
#include "mutation.h"
#include "linked_queue.h"
#include <time.h>

Queue* generate_inputs(int seed_count, int depth) {
    Queue* inputs = queue_create();
    const char* input_base = "linoone";

    for (int i = 0; i < seed_count; i++) {
        char* input_new = mutate(input_base);
        enqueue(inputs, input_new);
        for (int j = 1; j < depth; j++) {
            char* mutated = mutate(input_new);
            enqueue(inputs, input_new);
            free(input_new);
            input_new = mutated; 
        }
        free(input_new);
    }
    return inputs;
}


int main(int argc, char *argv[]) {
     if (argc < 4) {
        fprintf(stderr, "Usage: %s <program> <seed_count> <depth> <seed?>\n", argv[0]);
        return 1;
    }
    int seed_count = atoi(argv[2]);
    int depth = atoi(argv[3]);
    int random_seed = (argc > 3) ? atoi(argv[3]) : time(NULL); 
    srand(random_seed);


    Queue *q = generate_inputs(seed_count, depth);

    char *s;
    int count = 0;
    while ((s = dequeue(q)) != NULL) {
        printf("[%3d] %s\n", ++count, s);
        free(s);
    }

    queue_destroy(q);
    return 0;
}


/*
int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <program> <seed_count> <depth> <seed?>\n", argv[0]);
        return 1;
    }
    int seed_count = atoi(argv[2]);
    int depth = atoi(argv[3]);
    int random_seed = (argc > 3) ? atoi(argv[3]) : time(NULL); 
    srand(random_seed);

    char path[1024];
    snprintf(path, sizeof(path), "targets/%s", argv[1]);
    printf("Attempting to execute %s...", path);
    execl(path, argv[1], (char *)NULL);
    perror("Exec failure");
    return 1;
} */
