#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include<unistd.h>
sem_t s1, s2;

void *process1(void *arg) {
    sem_wait(&s1); // Lock s1
    printf("Process 1 acquired semaphore s1\n");

    // Simulate some work
    sleep(1);

    sem_wait(&s2); // Wait for s2 (deadlock)
    printf("Process 1 acquired semaphore s2\n");

    sem_post(&s2);
    sem_post(&s1);

    return NULL;
}

void *process2(void *arg) {
    sem_wait(&s2); // Lock s2
    printf("Process 2 acquired semaphore s2\n");

    // Simulate some work
    sleep(1);

    sem_wait(&s1); // Wait for s1 (deadlock)
    printf("Process 2 acquired semaphore s1\n");

    sem_post(&s1);
    sem_post(&s2);

    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Initialize semaphores
    sem_init(&s1, 0, 1);
    sem_init(&s2, 0, 1);

    // Create threads
    pthread_create(&t1, NULL, process1, NULL);
    pthread_create(&t2, NULL, process2, NULL);

    // Wait for threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}


/*
./prg3.out
Process 2 acquired semaphore s2
Process 1 acquired semaphore s1

*/
