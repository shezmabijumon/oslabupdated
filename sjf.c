#include<stdio.h>

struct process{
    int pid,at,bt;
    int wt,tat,ct;
    int executed;
};
int n;
struct process p[10],g[10];

void SJF();
void gantt();

void main(){
    int i;
    int total_wt=0,total_tat=0;
    printf("enter number of processes: ");
    scanf("%d",&n);
    printf("PID\tAT\tBT\n");
    for(i=0;i<n;i++){
        scanf("%d%d%d",&p[i].pid,&p[i].at,&p[i].bt);
    }
    SJF();
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

void SJF(){
    int currenttime,i,j=0;
    int shortestburst;
    int nextprocess;

    for(i=0;i<n;i++){
        p[i].executed=0;
    }
    currenttime=p[0].at;
    for(i=1;i<n;i++){
        if(p[i].at<currenttime){
            currenttime=p[i].at;
        }
    }
    while(1){
        shortestburst=100;
        nextprocess=-1;
        for(i=0;i<n;i++){
            if(!p[i].executed && currenttime>=p[i].at && p[i].bt<=shortestburst){
                shortestburst=p[i].bt;
                nextprocess=i;
            }
        }
        if (nextprocess==-1){
            break;
        }
        
        currenttime += p[nextprocess].bt;
        p[nextprocess].ct=currenttime;
        p[nextprocess].tat=p[nextprocess].ct-p[nextprocess].at;
        p[nextprocess].wt=p[nextprocess].tat-p[nextprocess].bt;
        p[nextprocess].executed=1;

        g[j]=p[nextprocess];
        j++;
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