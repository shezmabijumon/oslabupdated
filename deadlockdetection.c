#include<stdio.h>

void main(){
    int n,r;
    int avail[10],req[10][10],max[10][10],alloc[10][10],need[10][10];

    printf("Enter no.of processes: ");
    scanf("%d",&n);
    printf("Enter no.of resources: ");
    scanf("%d",&r);
    printf("enter available instances of each resource: ");
    for (int i = 0; i < r; i++){
        scanf("%d",&avail[i]);
    }
    /*printf("enter max matrix: ");
    for (int i = 0; i < n; i++){
        for (int j=0;j<r;j++){
            scanf("%d",&max[i][j]);
        }
    }*/
    printf("enter request matrix: ");
    for (int i = 0; i < n; i++){
        for (int j=0;j<r;j++){
            scanf("%d",&req[i][j]);
        }
    }
    printf("enter allocation matrix: ");
    for (int i = 0; i < n; i++){
        for (int j=0;j<r;j++){
            scanf("%d",&alloc[i][j]);
        }
    }
    /*for (int i = 0; i < n; i++){
        for (int j=0;j<r;j++){
            need[i][j]= max[i][j]-alloc[i][j];
        }
    }*/
    
    int ind=0,finish[10],safeseq[10],work[10];

    for (int i=0;i<n;i++){
        finish[i]=0;
    } 
    for (int i = 0; i < r; i++){
        work[i]=avail[i];
    }
    int count=0;
    while(count<n){  //
        for (int i = 0; i < n; i++){
            if(finish[i]==0){
                int flag=0;
                for (int j=0;j<r;j++){
                    if(req[i][j] > work[j]){
                        flag=1;
                        break;
                    }
                }
                if (flag==0){
                    safeseq[ind++]=i;
                    finish[i]=1;
                    count++;
                    for (int y=0;y<r;y++){
                        work[y] += alloc[i][y];
                    }
                }
            }
        }   
    }
    int d=0;
    for (int i = 0; i < n; i++){
        if (finish[i]==0){
            d=1;
            break;
        }
    }
    if(d==0){
        printf("SAFE SEQUENCE\n");
        for (int i = 0; i < n; i++){
            printf("P%d\t",safeseq[i]);
        }     
        printf("\n");
    }
    else{
        printf("Deadlock detected\n");
    }   
}