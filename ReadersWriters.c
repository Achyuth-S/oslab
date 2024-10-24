#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt; 
int read_count = 0, shared_data = 0;

void* reader(void* arg) {
    int id = *(int*)arg;
    sem_wait(&mutex);
    if (++read_count == 1) sem_wait(&wrt);
    sem_post(&mutex);

    printf("Reader %d reads data: %d\n", id, shared_data);
    sleep(1);

    sem_wait(&mutex);
    if (--read_count == 0) sem_post(&wrt);
    sem_post(&mutex);
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    sem_wait(&wrt);
    shared_data++;
    printf("Writer %d writes data: %d\n", id, shared_data);
    sleep(1);
    sem_post(&wrt);
    return NULL;
}

int main() {
    pthread_t r[5], w[2];
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    int ids[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 2; i++) pthread_create(&w[i], NULL, writer, &ids[i]);
    for (int i = 0; i < 5; i++) pthread_create(&r[i], NULL, reader, &ids[i]);

    for (int i = 0; i < 2; i++) pthread_join(w[i], NULL);
    for (int i = 0; i < 5; i++) pthread_join(r[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}