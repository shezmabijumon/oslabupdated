#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int data;
    int freq;
    int ts;
}frame;

void main(){
    int n,f;
    int time=0,pf=0;
    printf("enter the length of referential string: ");
    scanf("%d",&n);
    int s[30];
    printf("enter referential string: ");
    for (int i = 0; i < n; i++){
        scanf("%d",&s[i]);
    }
    printf("enter the no.of frames: ");
    scanf("%d",&f);
    frame fr[6];
    for (int i = 0; i < f; i++){
        fr[i].data=-1;
        fr[i].freq=0;
        fr[i].ts=0;
    }

    for (int i = 0; i < n; i++){
        time++;
        int j;
        for(j=0;j<f;j++){
            if(fr[j].data==s[i]){
                fr[j].freq++;
                //fr[j].ts=time;
                break;
            }
        }
        if(j==f){
            pf++;
            int ind=0;
            int min= fr[ind].freq;
            for(int k=0;k<f;k++){
                if(fr[k].freq <= min){
                    if(fr[k].freq < min){
                        min = fr[k].freq;
                        ind=k;
                    }
                    else{
                        if(fr[k].ts < fr[ind].ts){
                            min = fr[k].freq;
                            ind=k;
                        }
                    }
                }
            }
            fr[ind].data=s[i];
            fr[ind].freq = 1;
            fr[ind].ts=time;
        }
        for(int k=0;k<f;k++){
            printf("%d\t",fr[k].data);
        }
        if(j==f){
            printf("\tPF: %d\n",pf);
        }
        else{
            printf("\tHIT\n");
        }
    }
    printf("\nTotal no.of page faults = %d\n",pf);           
}