#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello from (pid: %d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork Failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process
        printf("/bin/ls (from child process)\n");
        char *myargs[3];
        myargs[0] = "/bin/ls";
        myargs[1] = NULL;
        execvp(myargs[0], myargs);        
    } else {
        // parent process
        // sleep(1);
        
        printf("bye (from parent process)\n");

    }
    return 0;
}