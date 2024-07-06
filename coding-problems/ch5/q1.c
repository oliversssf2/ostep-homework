#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("hello (pid: %d)\n", (int) getpid());
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork Failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process
        x = 1;
        printf("x in child process (x=1 in child process): %d\n", x);
    } else {
        // parent process
        x = 2;
        printf("x in parent process (x=2 in parent process): %d\n", x);
    }

}