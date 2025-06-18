#ifndef MUTATION_H
#define MUTATION_H

#define INPUT_SIZE 1024

#include <stdlib.h>
#include <string.h>

char* mutate(const char *input);
char* char_flip(char *mutated);
char* char_insert(char *mutated);
char* char_delete(char *mutated);

#endif // MUTATION_H
