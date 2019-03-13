#include <semaphore.h>
/*Compile the code by linking with -lpthread -lrt*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>
#define BUFFER_SIZE 10

extern sem_t sem_producer, sem_consumer;
extern pthread_mutex_t mutex;
extern int * buffer[BUFFER_SIZE];

void producer_a_byte(void)
{
    char c = 'A' + (rand() % 26);
    int index,status;
    if((status = sem_getvalue(&sem_consumer,&index))== 0){
        buffer[index] = c;
        printf("Produced : %c\n",c);
    } else {
        printf("sem_getval() returned %d", status);
    }
}

int main(int argc, char **argv)
{
    srand(time(0));
    while(1){
        sem_wait(&sem_producer);
        pthread_mutex_lock(&mutex); 
        producer_a_byte();
        sem_post(&sem_consumer);
        pthread_mutex_unlock(&mutex); 
    }
    
    printf("I am the producer\n");
    return 0;
}