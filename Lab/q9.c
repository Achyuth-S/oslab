#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int shmid = shmget(IPC_PRIVATE, sizeof(char), IPC_CREAT | 0666);
    char *shm = (char *)shmat(shmid, NULL, 0);
    char input;

    if (fork() == 0) {  // Child process
        sleep(5);  // Wait for parent to write the input
        *shm = (*shm == 'Z') ? 'A' : (*shm == 'z') ? 'a' : *shm + 1;
        shmdt(shm);
        exit(0);
    } else {  // Parent process
        printf("Enter an alphabet: ");
        scanf(" %c", &input);
        *shm = input;
        wait(NULL);  // Wait for child to finish
        printf("Parent received: %c\n", *shm);
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}
