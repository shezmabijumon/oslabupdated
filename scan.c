#include<stdio.h>
#include<stdlib.h>

int arr[30],n,d,head;

void sort(int a[],int m){
    int t;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < m-i-1; j++){
            if (a[j]>a[j+1]){
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }
}

void scan(){
    int disp,curr,headmov=0;
    int l[20],r[20];
    int left=0,right=0;
    for (int i = 0; i < n; i++){
        if(arr[i]<head){
            l[left++]=arr[i];
        }
        else{
            r[right++]=arr[i];
        }
    }
    sort(l,left);
    sort(r,right);
    r[right++]=d-1;
    for (int i = 0; i < right; i++){
        curr=r[i];
        disp=abs(curr - head);
        headmov += disp;
        head =curr;
        printf("%d\t", r[i]);
    }
    for (int i = left-1; i >= 0; i--){
        curr=l[i];
        disp=abs(head-curr);
        headmov += disp;
        head = curr;
        printf("%d\t", l[i]);
    }
    printf("\nTotal no of head movements:%d\n", headmov);    
}

void main(){
    printf("enter no.of disks: ");
    scanf("%d",&d);
    printf("enter no.of requests: ");
    scanf("%d",&n);
    printf("enter the requests: ");
    for (int i = 0; i < n; i++){
        scanf("%d",&arr[i]);
    }
    printf("enter position of head: ");
    scanf("%d",&head);
    scan();
}