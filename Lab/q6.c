#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, wrt;
int read_count = 0; // Count of readers

void* reader(void* arg) {
    sem_wait(&mutex);
    read_count++;
    if (read_count == 1)
        sem_wait(&wrt); // First reader locks the resource for writing
    sem_post(&mutex);

    // Reading (critical section)
    printf("Reader %d is reading.\n", *((int*)arg));

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)
        sem_post(&wrt); // Last reader unlocks the resource
    sem_post(&mutex);
    return NULL;
}

void* writer(void* arg) {
    sem_wait(&wrt); // Lock for writing

    // Writing (critical section)
    printf("Writer %d is writing.\n", *((int*)arg));

    sem_post(&wrt); // Unlock after writing
    return NULL;
}

int main() {
    pthread_t r[5], w[3]; // 5 readers, 3 writers
    int id[5] = {1, 2, 3, 4, 5}; // Reader/writer IDs

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create reader threads
    for (int i = 0; i < 5; i++)
        pthread_create(&r[i], NULL, reader, &id[i]);

    // Create writer threads
    for (int i = 0; i < 3; i++)
        pthread_create(&w[i], NULL, writer, &id[i]);

    // Join reader threads
    for (int i = 0; i < 5; i++)
        pthread_join(r[i], NULL);

    // Join writer threads
    for (int i = 0; i < 3; i++)
        pthread_join(w[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}
