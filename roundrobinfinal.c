#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NUM  25

typedef struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int queue_arrival;
    int rem_time;
} process;

typedef struct queue {
    int front, rear;
    process p[MAX_NUM];
} queue;

void init(queue* q) {
    q->front = q->rear = -1;
}

bool isEmpty(queue* q) {
    return q->rear == q->front;
}

void enqueue(queue* q, process pr) {
    if (q->rear == MAX_NUM - 1) return;
    q->p[++q->rear] = pr;
    for (int i = 0; i < q->rear; i++) {
        for (int j = 0; j < q->rear - i; j++) {
            if (q->p[j].queue_arrival > q->p[j+1].queue_arrival) {
                process temp = q->p[j];
                q->p[j] = q->p[j+1];
                q->p[j+1] = temp; 
            }
        }
    }
}

process* dequeue(queue* q) {
    if (!isEmpty(q)) {
        process *temp = &q->p[++q->front];
        if (q->front == q->rear) init(q);
        return temp;
    } else {
        return NULL;
    }
}

void printq(queue* q) {
    for (int i = q->front + 1; i <= q->rear; i++) {
        printf("%d ", q->p[i].pid);
    }
    printf("\n");
}

void rr(queue* q, int n) {
    int wt, ct, tt, qt;
    wt = ct = tt = 0;
    qt = 2;

    while (!isEmpty(q)) {
        process pr = *dequeue(q);
        if (pr.queue_arrival <= ct) {
            printf("P%d\t|", pr.pid);
            if (pr.rem_time > qt) {
                wt += ct - pr.queue_arrival;
                ct += qt;
                pr.rem_time -= qt;
                pr.queue_arrival = ct;
                enqueue(q, pr);
            } else {
                wt += ct - pr.queue_arrival;
                ct += pr.rem_time;
                tt += ct - pr.arrival_time;
                pr.rem_time = 0;
            }
        } else {
            ct = pr.arrival_time;
            enqueue(q, pr);
        }
    }
    printf("Average waiting time: %f\n", (float)wt/n);
    printf("Average turnaround time: %f\n", (float)tt/n);
}

int main() {
    queue q;
    init(&q);
    process p;
    printf("Enter arrival time and burst time for 4 processes:\n");
    for (int i = 0; i < 4; i++) {
        p.pid = i;
        printf("Process %d:\n", p.pid);
        printf("Arrival time: ");
        scanf("%d", &p.arrival_time);
        printf("Burst time: ");
        scanf("%d", &p.burst_time);
        p.queue_arrival = p.arrival_time;
        p.rem_time = p.burst_time;
        enqueue(&q, p);
    }
    rr(&q, 4);
    return 0;
}
