#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <ctype.h>

#define SHARED_MEMORY_SIZE sizeof(char) // Size of shared memory

int main() {
    // Create shared memory
    char *shared_memory = mmap(NULL, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE,
                               MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (shared_memory == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        sleep(1);  // Let parent write first
        
        // Read alphabet from shared memory
        char received_char = *shared_memory;
        printf("Child: Received character '%c' from Parent.\n", received_char);
        
        // Calculate next alphabet
        char next_char;
        if (received_char >= 'A' && received_char <= 'Z') {
            next_char = (received_char == 'Z') ? 'A' : received_char + 1;
        } else if (received_char >= 'a' && received_char <= 'z') {
            next_char = (received_char == 'z') ? 'a' : received_char + 1;
        } else {
            next_char = received_char; // In case of invalid input, return the same
        }

        // Write next alphabet back to shared memory
        *shared_memory = next_char;
        printf("Child: Sent character '%c' back to Parent.\n", next_char);

        exit(0);
    } else {
        // Parent process
        // Get input alphabet from user
        char input_char;
        printf("Parent: Enter an English alphabet: ");
        scanf(" %c", &input_char);

        // Write the character to shared memory
        *shared_memory = input_char;
        printf("Parent: Sent character '%c' to Child.\n", input_char);

        // Wait for the child process to respond
        wait(NULL);

        // Read the response from the shared memory
        char reply_char = *shared_memory;
        printf("Parent: Received character '%c' from Child.\n", reply_char);

        // Unmap shared memory
        munmap(shared_memory, SHARED_MEMORY_SIZE);
    }

    return 0;
}