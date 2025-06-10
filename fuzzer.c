#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program>\n Where the program is in targets/\n", argv[0]);
        return 1;
    }

    char path[1024];
    snprintf(path, sizeof(path), "targets/%s", argv[1]);
    printf("Attempting to execute %s...", path);
    execl(path, argv[1], (char *)NULL);
    perror("Exec failure");
    return 1;
}
