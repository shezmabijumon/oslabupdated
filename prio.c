#include<stdio.h>

struct process{
    int pid,at,bt;
    int wt,tat,ct;
    int executed,prio;
};
struct process p[10],g[10];
int n;

void PRIO();
void gantt();

void main(){
    int i;
    int total_wt=0,total_tat=0;
    printf("enter number of processes: ");
    scanf("%d",&n);
    printf("PID\tAT\tBT\tPRIO\n");
    for(i=0;i<n;i++){
        scanf("%d%d%d%d",&p[i].pid,&p[i].at,&p[i].bt,&p[i].prio);
    }
    PRIO();
    printf("PID\tAT\tBT\tTAT\tWT\n");
    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].tat,p[i].wt);
    }

    for(i=0;i<n;i++){
        total_tat+=p[i].tat;
        total_wt+=p[i].wt;
    }
    float avgwait = (total_wt + 0.0) / n;
    float avgturn = (total_tat + 0.0) / n;

    printf("Average Waiting Time: %.2f\n", avgwait);
    printf("Average Turnaround Time: %.2f\n", avgturn);

    gantt();
}
void PRIO(){
    int i,k=0;
    int currenttime=0,count=0;
    int highestprio,nextprocess;

    for ( i = 0; i < n; i++){
        p[i].executed=0;
    }
    
    while(count<n){
        highestprio=100;
        nextprocess=-1;
        for ( i = 0; i < n; i++){
            if (!p[i].executed && p[i].at <=currenttime && p[i].prio<highestprio){
                highestprio=p[i].prio;
                nextprocess=i;
            }            
        }
        if (nextprocess==-1){
            currenttime++;
            continue;
        }
        count++;
        currenttime+=p[nextprocess].bt;
        p[nextprocess].ct=currenttime;
        p[nextprocess].tat=p[nextprocess].ct-p[nextprocess].at;
        p[nextprocess].wt=p[nextprocess].tat-p[nextprocess].bt;
        p[nextprocess].executed=1;

        g[k]=p[nextprocess];
        k++;
    }
}
void gantt(){
    for (int i = 0; i < n; i++){
        printf("| P%d ",g[i].pid);
    }
    printf("|\n0");
    for (int i = 0; i < n; i++){
        printf("    %d",g[i].ct);
    }   
    printf("\n");
}