#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>

# define Maxterms 5
# define Buffersize 5
sem_t empty;
sem_t full;
pthread_mutex_t mutex;
int in=0,out=0;
int buffer[Buffersize];

void *producer(void *pno){
    int item;
    for(int i=0;i<Maxterms;i++){
        item=rand();
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in]=item;
        printf("Producer %d produced item %d at %d\n",*((int *)pno),buffer[in],in);
        in=(in+1)%Buffersize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}
void *consumer(void *cno){
    int item;
    for (int i = 0; i < Maxterms; i++){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item=buffer[out];
        printf("Consumer %d consumed item %d from %d\n",*((int *)cno),item,out);
        out=(out+1)%Buffersize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main(){
    pthread_t pro[5],con[5];                                    //create array for thread

    pthread_mutex_init(&mutex,NULL);
    sem_init(&empty,0,Buffersize);                              //initialize sem and lock
    sem_init(&full,0,0);

    int a[5]={1,2,3,4,5};

    for(int i=0;i<5;i++){                                      //pthread create
        pthread_create(&pro[i],NULL,(void *)producer,(void *)&a[i]);
    }
    for(int i=0;i<5;i++){
        pthread_create(&con[i],NULL,(void *)consumer,(void *)&a[i]);
    }
    for(int i=0;i<5;i++){                                        //pthread join
        pthread_join(pro[i],NULL);
    }
    for(int i=0;i<5;i++){
        pthread_join(con[i],NULL);
    }
    
    pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);                                           //destroy
	sem_destroy(&full);
	return 0;
}