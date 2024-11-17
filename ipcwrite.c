#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<string.h>

int main(){
    key_t key= ftok("shmfile",43);   //to generate unique key
    int shmid=shmget(key,1024,0666|IPC_CREAT);  //to get identifier
    printf("identifier for shared memory is %d\n",shmid);
    void* shared_memory=shmat(shmid,NULL,0); //process attached to shared memory segment
    printf("process attached at %p\n",shared_memory);
    printf("enter data to be written to the shared memory: ");
    char buff[100];
    scanf("%s",buff);
    strcpy(shared_memory,buff); //copied content from buffer to shared memory
    printf("data written to shared memory is %s\n",(char*)shared_memory);
    shmdt(shared_memory); //detach from shared memory
    return 0;
}