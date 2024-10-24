#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int num_items = *((int *)arg);
    for (int i = 0; i < num_items; i++) {
        sem_wait(&empty); // Wait if buffer is full
        pthread_mutex_lock(&mutex);

        // Produce item
        buffer[in] = i;
        printf("Producer produced: %d\n", i);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);  // Signal that buffer is not empty
    }
    return NULL;
}

void *consumer(void *arg) {
    int num_items = *((int *)arg);
    for (int i = 0; i < num_items; i++) {
        sem_wait(&full);  // Wait if buffer is empty
        pthread_mutex_lock(&mutex);

        // Consume item
        int item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // Signal that buffer is not full
    }
    return NULL;
}

int main() {
    int num_items;

    printf("Enter the number of items to produce/consume: ");
    scanf("%d", &num_items);

    pthread_t prod_thread, cons_thread;
    
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod_thread, NULL, producer, &num_items);
    pthread_create(&cons_thread, NULL, consumer, &num_items);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
