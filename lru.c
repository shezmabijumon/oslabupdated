#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int data;
    int ts; //timestamp
}frame;

void main(){
    int n,f;
    int time=0,pf=0;
    printf("enter length of referential string: ");
    scanf("%d",&n);
    int s[30];
    printf("enter referential string: ");
    for (int i = 0; i < n; i++){
        scanf("%d",&s[i]);        
    }
    printf("enter no.of frames: ");
    scanf("%d",&f);
    printf("\n");
    frame fr[6];
    for (int i = 0; i < f; i++){
        fr[i].data=-1;
        fr[i].ts=0;
    }

    for (int i = 0; i < n; i++){
        time++;
        int j;
        for(j=0;j<f;j++){
            if (fr[j].data==s[i]){
                fr[j].ts=time;
                break;
            }           
        }
        if (j==f){
            pf++;
            int ind=0;
            int min=fr[ind].ts;
            for (int j=0;j<f;j++){
                if (fr[j].ts < min){
                    min= fr[j].ts;
                    ind=j;
                }
            }
            fr[ind].data=s[i];
            fr[ind].ts=time;
        }
        for (int k = 0; k < f; k++){
            printf("%d\t", fr[k].data);
        }
        if (j == f){
            printf("\tPF: %d\n", pf);
        }
        else{
            printf("\tHIT\n");
        }
    }
    printf("\nTotal no.of page faults = %d\n",pf);        
}