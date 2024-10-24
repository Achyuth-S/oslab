#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    // Create a child process using fork()
    pid_t pid = fork();

    if (pid < 0) {
        // If fork() returns a negative value, creation of the child process failed
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        // This block is executed by the child process
        printf("Child Process:\n");
        printf("PID of Child: %d\n", getpid());    // Get the PID of the child process
        printf("PPID of Child: %d\n", getppid());  // Get the Parent PID (PPID) of the child process
        printf("This is the message from the Child process!\n\n");
    }
    else {
        // This block is executed by the parent process
        wait(NULL);  // Wait for the child process to finish (optional but ensures proper order)
        printf("Parent Process:\n");
        printf("PID of Parent: %d\n", getpid());    // Get the PID of the parent process
        printf("PPID of Parent: %d\n", getppid());  // Get the Parent PID (PPID) of the parent process
        printf("This is the message from the Parent process!\n\n");
    }

    return 0;
}