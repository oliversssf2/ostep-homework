#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello from (pid: %d)\n", (int) getpid());

    int pipefd[2];
    char buf;
    if (pipe(pipefd) == -1) {
        fprintf(stderr, "Pipe Creation Failed\n");
        exit(-1);
    }

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork Failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process
        int rc2 = fork();
        if (rc2 < 0) {
            fprintf(stderr, "Second Fork Failed\n");
            exit(1);
        } else if (rc2 == 0) {
            // Read from the child of child process
            close(pipefd[1]); // Close write end
            while (read(pipefd[0], &buf, 1) > 0)
                write(STDOUT_FILENO, &buf, 1);
            
            write(STDOUT_FILENO, "\n", 1);
            close(pipefd[0]);
            exit(0);
        } else {
            // Write from the child process
            close(pipefd[0]); // Close Read End
            write(pipefd[1], "message1\n", 9);
            close(pipefd[1]); // Close write end too
            wait(NULL);
            exit(0);
        }
    } else {
        // parent process
        // wait(): on success, returns the process ID of the terminated child; on error, -1  is  returned.
        printf("bye (from parent process)\n");

    }
    return 0;
}