#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello from (pid: %d)\n", (int) getpid());
    int status, pid;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork Failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process
        printf("/bin/ls (from child process)\n");   
        int wait_rc = wait(NULL);
        printf("wait() returns {%d} in the child process", wait_rc);        
        char *myargs[2];
        myargs[0] = "/bin/ls";
        myargs[1] = NULL;
        execvp(myargs[0], myargs);        
    } else {
        // parent process
        // wait(): on success, returns the process ID of the terminated child; on error, -1  is  returned.
        pid = wait(&status); 
        if(WIFEXITED(status))
            printf("normal termination of child (%d), exit status = %d\n", pid, WEXITSTATUS(status));
        printf("Goodbye from parent (%d)\n", getpid());

    }
    return 0;
}