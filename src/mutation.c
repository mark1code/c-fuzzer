#include <stdlib.h>
#include <string.h>
#include "mutation.h"

static char* copy_input(const char *input) {
    char *copy = malloc(strlen(input) + 1);
    if (copy) strcpy(copy, input);
    return copy;
}

char* mutate(const char *input) {
    char *mutated = copy_input(input);
    if (!mutated) return NULL;

    if (strlen(mutated) == 0) {
        mutated[0] = (char)(rand() % 26 + 'a');
        mutated[1] = '\0';
        return mutated;
    }

    switch (rand() % 3) {
        case 0:
            mutated = char_delete(mutated);
            break;
        case 1:
            mutated = char_insert(mutated);
            break;
        case 2:
            mutated = char_flip(mutated);
            break;
        default:
            mutated = char_insert(mutated);
    }
    return mutated;
}

char* char_delete(char *mutated) {
    int len = strlen(mutated);
    if (len == 0) return mutated;
    int random_pos = rand() % len;
    int rsubstring_pos = random_pos + 1;
    int rsubstring_len = len - random_pos;
    memmove(&mutated[random_pos], &mutated[rsubstring_pos], rsubstring_len);
    return mutated;
}

char* char_insert(char *mutated) {
    int len = strlen(mutated);
    if (len == 0 || len > INPUT_SIZE - 1) return mutated;
    int random_pos = rand() % len;
    char random_asc = (char)(rand() % 128);
    int rsubstring_pos = random_pos + 1;
    int rsubstring_len = len - random_pos + 1;
    memmove(&mutated[rsubstring_pos], &mutated[random_pos], rsubstring_len);
    mutated[random_pos] = random_asc;
    return mutated;
}

char* char_flip(char *mutated) {
    int len = strlen(mutated);
    if (len == 0) return mutated;
    int random_pos = rand() % len;
    mutated[random_pos] ^= 1 << (rand() % 7);
    return mutated;
}

