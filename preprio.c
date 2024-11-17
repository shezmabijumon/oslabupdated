#include<stdio.h>

struct process{
    int pid,at,bt;
    int wt,tat,ct;
    int rembt;
    int executed,prio;
};
struct process p[10];
typedef struct{
    int id;
    int time; //time of execution
} gp;
gp g[100];
int n;
int k=0;

void PREPRIO();
void gantt();

void main(){
    int i;
    int total_wt=0, total_tat=0;
    printf("enter number of processes: ");
    scanf("%d",&n);
    printf("PID\tAT\tBT\tPRIO\n");
    for(i=0;i<n;i++){
        scanf("%d%d%d%d",&p[i].pid,&p[i].at,&p[i].bt,&p[i].prio);
        p[i].rembt=p[i].bt;
    }
    PREPRIO();
    printf("PID\tAT\tBT\tTAT\tWT\n");
    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].tat,p[i].wt);
    }
    gantt();

    for(i=0;i<n;i++){
        total_tat+=p[i].tat;
        total_wt+=p[i].wt;
    }
    float avgwait = (total_wt + 0.0) / n;
    float avgturn = (total_tat + 0.0) / n;

    printf("Average Waiting Time: %.2f\n", avgwait);
    printf("Average Turnaround Time: %.2f\n", avgturn);

}
void PREPRIO(){
    int completed=0;
    int currenttime=0;

    for (int i = 0; i < n; i++) {
        p[i].executed = 0;
    }

    while(completed!=n){
        int highprio=100;
        int nextprocess=-1;
        for (int i = 0; i < n; i++){
            if(!p[i].executed && p[i].at<=currenttime && p[i].prio<highprio){
                highprio=p[i].prio;
                nextprocess=i;
            }
        }
        
        if (nextprocess==-1){
            currenttime++;
            continue;
        }
        if(k==0 || g[k-1].id!=p[nextprocess].pid){
            g[k].id=p[nextprocess].pid;
            g[k].time=currenttime;
            k++;
        }
        else{
            g[k-1].time=currenttime;
        }
        p[nextprocess].rembt--;
        currenttime++;

        if (p[nextprocess].rembt==0){
            p[nextprocess].executed = 1;
            p[nextprocess].ct = currenttime;
            p[nextprocess].tat = p[nextprocess].ct - p[nextprocess].at;
            p[nextprocess].wt = p[nextprocess].tat - p[nextprocess].bt;
            completed++;
        }       
    }
}
void gantt(){
    for (int i = 0; i < n; i++){
        printf("| P%d ",g[i].id);
    }
    printf("|\n0");
    for (int i = 0; i < n; i++){
        printf("    %d",g[i].time);
    }   
    printf("\n");
}