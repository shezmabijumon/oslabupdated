#include<stdio.h>
#include<stdlib.h>

int n,arr[30],head;

void fcfsd(){
    int disp,curr,headmov=0;
    for (int i = 0; i < n; i++){
        curr=arr[i];
        disp= abs(head - curr);
        headmov += disp;
        head=curr;
    }
    printf("SEEK SEQUENCE:\n");
    for (int i = 0; i < n; i++){
        printf("%d\t", arr[i]);
    }
    printf("\nTotal number of seek operations: %d\n", headmov);    
}

void main(){
    printf("enter no.of requests: ");
    scanf("%d",&n);
    printf("enter the requests: ");
    for (int i = 0; i < n; i++){
        scanf("%d",&arr[i]);
    }
    printf("enter position of head: ");
    scanf("%d",&head);
    fcfsd();    
}