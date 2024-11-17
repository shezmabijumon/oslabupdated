#include<stdio.h>
#include<stdlib.h>

void main(){
    int n,m,count=0,pf=0;
    printf("enter the length of referential string: ");
    scanf("%d",&n);
    int s[30];
    printf("enter the referential string: ");
    for (int i = 0; i < n; i++){
        scanf("%d",&s[i]);
    }
    /*printf("The referrence string :\n");
    for (int i = 0; i < n; i++){
        printf("%d,", s[i]);
    }*/
    printf("enter the no.of frames: ");
    scanf("%d",&m);
    printf("\n");
    int f[6];
    for (int i = 0; i < m; i++){
        f[i]=-1;
    }
    for (int i = 0; i < n; i++){
        int j;
        for (j = 0; j < m; j++){
            if (f[j]==s[i]){
                break;
            }
        }
        if (j==m){
            f[count]=s[i];
            count= (count+1)%m;
            pf++;
        }
        //to print frames
        for (int k=0; k<m; k++){
            printf("%d\t",f[k]);
        }
        if (j==m){
            printf("\tPF: %d\n",pf);
        }
        else{
            printf("\tHIT\n");
        }
    }
    printf("\nTotal no.of page faults = %d\n",pf);
}