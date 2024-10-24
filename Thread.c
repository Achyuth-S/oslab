#include <stdio.h>
#include <pthread.h>

typedef struct { int *arr, size, evenSum, oddSum; } SumData;

void *sumEven(void *arg) {
    SumData *data = (SumData *)arg;
    for (int i = 0; i < data->size; i++) 
        if (data->arr[i] % 2 == 0) data->evenSum += data->arr[i];
    return NULL;
}

void *sumOdd(void *arg) {
    SumData *data = (SumData *)arg;
    for (int i = 0; i < data->size; i++) 
        if (data->arr[i] % 2 != 0) data->oddSum += data->arr[i];
    return NULL;
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    SumData data = {arr, n, 0, 0};
    pthread_t evenThread, oddThread;

    pthread_create(&evenThread, NULL, sumEven, &data);
    pthread_create(&oddThread, NULL, sumOdd, &data);
    
    pthread_join(evenThread, NULL);
    pthread_join(oddThread, NULL);

    printf("Even Sum: %d\nOdd Sum: %d\n", data.evenSum, data.oddSum);
    return 0;
}