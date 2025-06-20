#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
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

int fuzz(Queue *inputs, const char *target_path) {
    int iteration = 0;
    char *input;
    while ((input = dequeue(inputs))) { 
        int pipefd[2]; int pid;
        if (pipe(pipefd) < 0) return EXIT_FAILURE;
        if ((pid = fork()) == 0) {
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[1]);
            execl(target_path, target_path, NULL);
            perror("execl failure");
            exit(EXIT_FAILURE);
        }
        else {
            close(pipefd[0]); 
            write(pipefd[1], input, strlen(input));
            close(pipefd[1]);
            waitpid(pid, NULL, 0);
        }
        free(input);
        iteration++;
        printf("iteration: %d complete\n", iteration);
    }
    printf("FINISHED!\n");
    return EXIT_SUCCESS;
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

    if (strchr(argv[1], '/')) {
        fprintf(stderr, "Invalid target: must not contain ''/\n");
        return EXIT_FAILURE;
    }
    char path[1024];
    if (snprintf(path, sizeof(path), "targets/%s", argv[1]) > (int)sizeof(path)- 1) {
        fprintf(stderr, "Invalid target: name too long\n");
        return EXIT_FAILURE;
    }

    Queue *inputs = generate_inputs(seed_count, depth);

    printf("Attempting to fuzz %s...\n", path);
        
    /*
    char *s;
    int count = 0;
    while ((s = dequeue(q)) != NULL) {
        printf("[%3d] %s\n", ++count, s);
        free(s);
    }
    queue_destroy(q);
    */
    return fuzz(inputs, path);
}

