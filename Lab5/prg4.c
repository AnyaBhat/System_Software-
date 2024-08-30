#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("Child Process (PID: %d) is terminating...\n", getpid());
        exit(EXIT_SUCCESS);  
    } else {
        printf("Parent Process (PID: %d) is sleeping...\n", getpid());
        sleep(60);  
        printf("Parent Process (PID: %d) is exiting...\n", getpid());
        exit(EXIT_SUCCESS);  
    }

    return 0;
}
