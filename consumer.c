#include <semaphore.h>
/*Compile the code by linking with -lpthread -lrt*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <pthread.h>
#define BUFFER_SIZE 10

extern sem_t sem_producer, sem_consumer;
extern pthread_mutex_t mutex;
extern int * buffer[BUFFER_SIZE];

void consume_a_byte(void)
{
    int index, status;
    char c;
    if((status = sem_getvalue(&sem_consumer,&index)) == 0) {
        c = buffer[index];
        printf("Consumed %d\n",c);
    } else {
        printf("sem_getval() returned %d", status);
    }
}

int main(int argc, char **argv)
{
    while(1){
        sem_wait(&sem_consumer);
        pthread_mutex_lock(&mutex); 
        consume_a_byte();
        sem_post(&sem_producer);
        pthread_mutex_unlock(&mutex); 
    }
    
    printf("I am the consumer\n");
    return 0;
}