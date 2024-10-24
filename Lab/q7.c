#include <stdio.h>

#define P 5  // Number of processes
#define R 3  // Number of resource types

int main() {
    int i, j, k;
    
    // Available resources
    int available[R];
    
    // Maximum demand of each process
    int max[P][R];

    // Allocation for each process
    int allocation[P][R];

    // Need matrix
    int need[P][R];

    // Input available resources
    printf("Enter the available resources for %d types: ", R);
    for (i = 0; i < R; i++)
        scanf("%d", &available[i]);

    // Input maximum demand for each process
    printf("Enter the maximum resources matrix (%d x %d):\n", P, R);
    for (i = 0; i < P; i++) {
        printf("For process %d: ", i);
        for (j = 0; j < R; j++)
            scanf("%d", &max[i][j]);
    }

    // Input allocation matrix for each process
    printf("Enter the allocation matrix (%d x %d):\n", P, R);
    for (i = 0; i < P; i++) {
        printf("For process %d: ", i);
        for (j = 0; j < R; j++)
            scanf("%d", &allocation[i][j]);
    }

    // Calculate the Need matrix
    for (i = 0; i < P; i++)
        for (j = 0; j < R; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    int finish[P] = {0};  // Track if a process is finished
    int safeSequence[P];
    int work[R];
    
    // Initialize work as available resources
    for (i = 0; i < R; i++)
        work[i] = available[i];

    int count = 0;
    while (count < P) {
        int found = 0;
        for (i = 0; i < P; i++) {
            if (!finish[i]) {
                for (j = 0; j < R; j++)
                    if (need[i][j] > work[j])
                        break;

                // If all resources can be allocated
                if (j == R) {
                    for (k = 0; k < R; k++)
                        work[k] += allocation[i][k];
                    
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("The system is in an unsafe state.\n");
            return 0;
        }
    }

    // Safe sequence found
    printf("The system is in a safe state.\nSafe sequence is: ");
    for (i = 0; i < P; i++)
        printf("%d ", safeSequence[i]);
    printf("\n");

    return 0;
}
