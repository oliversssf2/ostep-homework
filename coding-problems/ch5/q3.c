#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork Failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process
        printf("hello (from child process)\n");
    } else {
        // parent process
        sleep(1);
        printf("bye (from parent process)\n");

    }
    return 0;
}