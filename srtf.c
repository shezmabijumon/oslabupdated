#include <stdio.h>

typedef struct {
    int id, at, bt, wt, tt, ct, rt;
} process;
int n;
process p[n];
int gantt_chart[100];
int gantt_time[100];
int gantt_len;

void srtf();
void gantt();

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    process p[n];
    printf("Enter process id, arrival time, and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &p[i].id, &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt; // Initialize remaining time
    }

    srtf();

    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].wt, p[i].tt,p[i].ct);
    }

    gantt();
    return 0;
}

void srtf() {
    int t = 0, count = 0;
    int cp; // Current process index
    int gantt_index = 0;

    // Initialize remaining times
    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
    }

    while (count < n) {
        int nextprocess=-1;
        int min_time=100;

        for (int i = 0; i < n; i++){
            if (p[i].at<=t && p[i].rt < min_time && p[i].rt>0 ){
                nextprocess=i;
                min_time=p[i].rt;
            }
        }

        if (nextprocess == -1) {
            t++; // Increment time if no process is ready
            continue;
        }

        // Execute the process for one unit of time
        p[nextprocess].rt--;
        t++;

        // Log the Gantt chart entry
        if (gantt_index == 0 || gantt_chart[gantt_index - 1] != p[nextprocess].id) {
            gantt_chart[gantt_index] = p[nextprocess].id;
            gantt_time[gantt_index] = t;
            gantt_index++;
        } else {
            gantt_time[gantt_index - 1] = t;
        }

        // If process completes, update its completion time
        if (p[nextprocess].rt == 0) {
            count++;
            p[nextprocess].ct = t;
        }
    }

    gantt_len = gantt_index;

    // Calculate turnaround time and waiting time
    for (int i = 0; i < n; i++) {
        p[i].tt = p[i].ct - p[i].at; // Turnaround time
        p[i].wt = p[i].tt - p[i].bt; // Waiting time
    }
}

void gantt() {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < gantt_len; i++) {
        printf("| P%d ", gantt_chart[i]);
    }
    printf("|\n");

    printf("0");
    for (int i = 0; i < gantt_len; i++) {
        printf("    %d", gantt_time[i]);
    }
    printf("\n");
}