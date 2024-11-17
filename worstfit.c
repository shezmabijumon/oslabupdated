#include<stdio.h>
#include<stdlib.h>

struct block{
    int id;
    int size;
    int alloc;  //stores block id of allocated block to a process
}mem[10],pro[10];
int m,n;
void sort(){
    struct block t;
    for (int i = 0; i < m; i++){
        for(int j = 0; j < m-i-1; j++){
            if (mem[j].size < mem[j+1].size){
                t=mem[j];
                mem[j]=mem[j+1];
                mem[j+1]=t;
            }
        }
    }
}
void worstfit(){
    for (int i = 0; i < n; i++){
        sort();
        for (int j=0; j<m; j++){
            if (mem[j].size >= pro[i].size){
                pro[i].alloc=mem[j].id;
                mem[j].size -= pro[i].size;
                break;
            }
        }
        if (pro[i].alloc==-1){
            printf("Process P%d couldnot be allocated any memory block\n",pro[i].id);
        }     
    } 
}

void main(){
    printf("\t\t MEMORY MANAGEMENT\n");
    printf("\t\t-------------------\n");
    printf("enter number of memory blocks: ");
    scanf("%d",&m);
    printf("Memoryblock\tsize");
    for (int i = 0; i < m; i++){
        mem[i].id=i+1;
        printf("M%d\t",mem[i].id);
        scanf("%d",mem[i].size);
    }
    printf("enter number of processes: ");
    scanf("%d",&n);
    printf("Process\tsize");
    for (int i = 0; i < n; i++){
        pro[i].id=i+1;
        printf("P%d\t",pro[i].id);
        scanf("%d",pro[i].size);
        pro[i].alloc=-1;
    }
    worstfit();
    printf("\nProgram Details\n");
    printf("Progm Id\tProgm Size\tId of Block allocated\n");
    for (int i = 0; i < m; i++){
        if (pro[i].alloc==-1){
            printf("   %d   \t\t    %d  \t\t\tnil\n", pro[i].id, pro[i].size);           
        }
        else{
            printf("   %d   \t\t    %d  \t\t\t%d\n", pro[i].id, pro[i].size, pro[i].alloc);
        }
    }

}