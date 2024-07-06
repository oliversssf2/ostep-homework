#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    printf("hello (pid: %d)\n", (int) getpid());
    int fd = open("./q2.txt",  O_CREAT| O_RDWR |O_TRUNC, S_IRWXU);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork Failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process
        write(fd, "writing from child process\n", 27);
    } else {
        // parent process
        // fputs("writing from parent process\n", file);
        write(fd, "writing from parent process\n", 28);
    }
    // close(file);
    return 0;
}