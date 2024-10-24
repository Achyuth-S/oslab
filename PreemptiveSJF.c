#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;          // Process ID
    int arrival_time; // Arrival time of the process
    int burst_time;   // Burst time of the process
    int remaining_time; // Remaining burst time of the process
    int completion_time; // Completion time of the process
    int waiting_time; // Waiting time of the process
    int turnaround_time; // Turnaround time of the process
    int is_completed;  // Whether the process is completed
};

// Function to find the process with the shortest remaining time
int findShortestJob(struct Process processes[], int n, int current_time) {
    int min_time = INT_MAX;
    int shortest_job = -1;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && 
            !processes[i].is_completed && 
            processes[i].remaining_time < min_time) {
            min_time = processes[i].remaining_time;
            shortest_job = i;
        }
    }
    return shortest_job;
}

// Function to calculate waiting and turnaround time
void calculateTimes(struct Process processes[], int n) {
    int completed = 0, current_time = 0;
    while (completed < n) {
        int idx = findShortestJob(processes, n, current_time);
        if (idx == -1) {
            current_time++; // If no process is ready, advance time
            continue;
        }

        // Process the selected process for 1 unit time
        processes[idx].remaining_time--;
        current_time++;

        // If the process is completed
        if (processes[idx].remaining_time == 0) {
            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            processes[idx].is_completed = 1;
            completed++;
        }
    }
}

// Function to display process details
void displayProcesses(struct Process processes[], int n) {
    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
            processes[i].pid, 
            processes[i].arrival_time, 
            processes[i].burst_time, 
            processes[i].completion_time, 
            processes[i].turnaround_time, 
            processes[i].waiting_time);
    }
}

// Main function
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time; // Initialize remaining time to burst time
        processes[i].is_completed = 0; // Initialize all processes as incomplete
    }

    // Calculate waiting and turnaround times
    calculateTimes(processes, n);

    // Display process details
    displayProcesses(processes, n);

    return 0;
}