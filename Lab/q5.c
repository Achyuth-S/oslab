#include <stdio.h>

#define MAX 10

typedef struct {
    int pid, at, bt, rt, ct, wt, tat;
} Process;

int main() {
    Process p[MAX];
    int n, completed = 0, time = 0, min = 0;
    int total_wt = 0, total_tat = 0, is_running = 0;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d Arrival Time: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("P%d Burst Time: ", p[i].pid);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
    }

    while (completed != n) {
        min = -1;

        // Find process with shortest remaining time and has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                if (min == -1 || p[i].rt < p[min].rt)
                    min = i;
            }
        }

        if (min != -1) {
            p[min].rt--;
            time++;
            if (p[min].rt == 0) {
                completed++;
                p[min].ct = time;
                p[min].tat = p[min].ct - p[min].at;
                p[min].wt = p[min].tat - p[min].bt;
                total_wt += p[min].wt;
                total_tat += p[min].tat;
            }
        } else {
            time++;
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", (float)total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);

    return 0;
}
