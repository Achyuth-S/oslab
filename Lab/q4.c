#include <stdio.h>
#include <pthread.h>

int even_sum = 0, odd_sum = 0;
int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int n = sizeof(arr) / sizeof(arr[0]);

void* sum_even(void* arg) {
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            even_sum += arr[i];
        }
    }
    return NULL;
}

void* sum_odd(void* arg) {
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 != 0) {
            odd_sum += arr[i];
        }
    }
    return NULL;
}

int main() {
    pthread_t even_thread, odd_thread;

    // Create threads
    pthread_create(&even_thread, NULL, sum_even, NULL);
    pthread_create(&odd_thread, NULL, sum_odd, NULL);

    // Wait for both threads to finish
    pthread_join(even_thread, NULL);
    pthread_join(odd_thread, NULL);

    // Output results
    printf("Sum of even numbers: %d\n", even_sum);
    printf("Sum of odd numbers: %d\n", odd_sum);

    return 0;
}
