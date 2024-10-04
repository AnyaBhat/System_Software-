#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_PRODUCE 20

int buf[BUFFER_SIZE], f = 0, r = 0;
sem_t mutex, full, empty;
int produced_count = 0; // Count of produced items
int consumed_count = 0; // Count of consumed items

void *produce(void *arg) {
    int i;
    for (i = 0; i < 20; i++) { // Attempt to produce 20 items
        sem_wait(&empty);
        sem_wait(&mutex);

        // Check if the producer can produce more than the consumer has consumed
        if (produced_count - consumed_count < MAX_PRODUCE) {
            printf("Produced item is %d\n", i);
            buf[r] = i; // Produce item
            r = (r + 1) % BUFFER_SIZE;
            produced_count++; // Increment produced count
        } else {
            printf("Producer is waiting, cannot produce more than %d items over consumed.\n", MAX_PRODUCE);
        }

        sem_post(&mutex);
        sem_post(&full);
        sleep(1); // Simulate time taken to produce
    }
    return NULL;
}

void *consume(void *arg) {
    int item, i;
    for (i = 0; i < 20; i++) { // Attempt to consume 20 items
        sem_wait(&full);
        sem_wait(&mutex);

        item = buf[f]; // Consume item
        printf("Consumed item is %d\n", item);
        f = (f + 1) % BUFFER_SIZE;
        consumed_count++; // Increment consumed count

        sem_post(&mutex);
        sem_post(&empty);
        sleep(1); // Simulate time taken to consume
    }
    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);

    pthread_create(&tid1, NULL, produce, NULL);
    pthread_create(&tid2, NULL, consume, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}

/*

Produced item: 0
Consumed item: 0
Produced item: 1
Consumed item: 1
Produced item: 2
Consumed item: 2
Produced item: 3
Consumed item: 3
Produced item: 4
Consumed item: 4
Produced item: 5
Consumed item: 5
Produced item: 6
Consumed item: 6
Produced item: 7
Consumed item: 7
Produced item: 8
Consumed item: 8
Produced item: 9
Consumed item: 9
Produced item: 10
Consumed item: 10
Produced item: 11
Consumed item: 11
Produced item: 12
Consumed item: 12
Produced item: 13
Consumed item: 13
Produced item: 14
Consumed item: 14
Produced item: 15
Consumed item: 15
Produced item: 16
Consumed item: 16
Produced item: 17
Consumed item: 17
Produced item: 18
Consumed item: 18
Produced item: 19
Consumed item: 19
*/
