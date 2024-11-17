#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#define NumPhilo 2
#define maxcycles 2     //max no.of times one can eat

int eating_cycles[NumPhilo];  //tracks the number of times each philosopher has eaten
sem_t forks[NumPhilo],mutex;
pthread_t philosophers[NumPhilo];

void *philosopher (void *arg){
    int id= *((int *)arg);
    int left_fork= id;
    int right_fork= (id+1)%NumPhilo;
    int eatingcount=0;

    while(eatingcount < maxcycles){
        printf("Philosopher %d has started thinking and is not eating\n",id);  //thinking
        sleep(rand() % 3 + 1);  //philo thinks for a random amount of time
        sem_wait(&mutex);
        sem_wait(&forks[left_fork]);
        sem_wait(&forks[right_fork]);
        sem_post(&mutex);
        printf("Philosopher %d has stopped thinking and started eating\n",id);  //eating
        sleep(rand() % 3 + 1);
        eating_cycles[id]++;
        eatingcount++;
        sem_post(&forks[left_fork]);
        sem_post(&forks[right_fork]);
    }
    return NULL;
}

int main(){
    int i;
    srand(time(NULL));
    sem_init(&mutex,0,1);
    for ( i = 0; i < NumPhilo; i++){
        sem_init(&forks[i],0,1);
    }
    //create philo thread
    for(i=0;i<NumPhilo;i++){
        int *id=(int *)malloc(sizeof(int));
        *id = i;
        pthread_create(&philosophers[i],NULL,philosopher,id);
    }
    for(i=0;i<NumPhilo;i++){
        pthread_join(philosophers[i],NULL);
    }
    sem_destroy(&mutex);
    for ( i = 0; i < NumPhilo; i++){
        sem_destroy(&forks[i]);
    }
    for (i = 0; i < NumPhilo; i++)
        printf("Philosopher %d ate %d times\n", i, eating_cycles[i]);
    return 0;
}