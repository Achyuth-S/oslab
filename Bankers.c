#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

// Function to find if the system is in a safe state
bool isSafe(int processes[], int avail[], int maxm[][R], int allot[][R]) {
    int need[P][R];
    int work[R];
    bool finish[P];
    
    // Calculate the Need matrix (Need[i][j] = Max[i][j] - Allot[i][j])
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = maxm[i][j] - allot[i][j];
        }
    }

    // Initialize work array to available resources
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }
    
    // Initialize finish array to false
    for (int i = 0; i < P; i++) {
        finish[i] = false;
    }

    // Safe sequence array
    int safeSeq[P];
    int count = 0;

    // Find processes that can finish
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (finish[p] == false) {
                int j;
                // Check if all need resources are less than or equal to work resources
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }
                // If all needs are satisfied
                if (j == R) {
                    // Add allocated resources of this process to work
                    for (int k = 0; k < R; k++) {
                        work[k] += allot[p][k];
                    }
                    // Mark process as finished
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        // If no process can proceed, system is not in safe state
        if (found == false) {
            printf("System is not in a safe state\n");
            return false;
        }
    }
    
    // If all processes are finished, system is in a safe state
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++) {
        printf("%d ", safeSeq[i]);
    }
    printf("\n");
    
    return true;
}

int main() {
    int processes[] = {0, 1, 2, 3, 4};

    // Available instances of resources
    int avail[] = {3, 3, 2};

    // Maximum demand of each process
    int maxm[][R] = {{7, 5, 3},
                     {3, 2, 2},
                     {9, 0, 2},
                     {2, 2, 2},
                     {4, 3, 3}};

    // Resources allocated to each process
    int allot[][R] = {{0, 1, 0},
                      {2, 0, 0},
                      {3, 0, 2},
                      {2, 1, 1},
                      {0, 0, 2}};

    // Check system for safe state
    isSafe(processes, avail, maxm, allot);

    return 0;
}