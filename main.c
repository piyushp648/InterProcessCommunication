#include <semaphore.h>
/*Compile the code by linking with -lpthread -lrt*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define BUFFER_SIZE 10

sem_t mutex, producer, consumer;
int *buffer[BUFFER_SIZE];

int main(int argc, char **argv)
{
    pid_t pid_producer , pid_consumer;
    int status;
    sem_init(&mutex, 1, 1);
    sem_init(&producer, 1, BUFFER_SIZE);
    sem_init(&consumer, 1, 0);

    pid_producer = fork();
    if (pid_producer == 0) {
        status  = execvp("./producer.o",NULL);
        
    } else {
        waitpid(pid_producer,NULL,WUNTRACED);
        pid_consumer = fork();
        if(pid_consumer == 0) {
            status = execvp("./consumer.o", NULL);
        } else {
            waitpid(pid_consumer,NULL,WUNTRACED);
        }
    }
    
    return 0;
}
