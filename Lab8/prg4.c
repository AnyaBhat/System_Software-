#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CHAIRS 3        // Number of chairs in the waiting room
#define CUSTOMERS 5    // Total customers

sem_t barberReady;       // Barber semaphore
sem_t customerReady;     // Customer semaphore
sem_t mutex;             // Mutex for critical section

int waitingCustomers = 0; // Number of waiting customers

void* barber(void* arg) {
    while (1) {
        sem_wait(&customerReady); // Wait for a customer
        sem_wait(&mutex);         // Enter critical section

        waitingCustomers--;        // A customer is taken
        printf("Barber is cutting hair. Customers waiting: %d\n", waitingCustomers);

        sem_post(&barberReady);    // Signal that the barber is ready
        sem_post(&mutex);          // Leave critical section

        sleep(2);                  // Simulate time taken to cut hair
    }
}

void* customer(void* arg) {
    int id = *(int*)arg;

    sem_wait(&mutex);             // Enter critical section
    if (waitingCustomers < CHAIRS) { // If there is space in the waiting room
        waitingCustomers++;        // Customer is added to waiting
        printf("Customer %d is waiting. Customers waiting: %d\n", id, waitingCustomers);
        sem_post(&customerReady);  // Signal that a customer is ready
        sem_post(&mutex);          // Leave critical section

        sem_wait(&barberReady);    // Wait for the barber to be ready
        printf("Customer %d is getting a haircut.\n", id);
    } else {
        printf("Customer %d leaves because there are no chairs available.\n", id);
        sem_post(&mutex);          // Leave critical section
    }

    return NULL;
}

int main() {
    pthread_t barberThread;
    pthread_t customers[CUSTOMERS];
    int customerIds[CUSTOMERS];

    sem_init(&barberReady, 0, 0);    // Barber starts sleeping
    sem_init(&customerReady, 0, 0);  // No customer ready initially
    sem_init(&mutex, 0, 1);          // Mutex for critical section

    // Create barber thread
    printf("Barber is sleeping\n");
    pthread_create(&barberThread, NULL, barber, NULL);

    // Seed random number generator
    srand(time(NULL));

    // Create customer threads
    for (int i = 0; i < CUSTOMERS; i++) {
        customerIds[i] = i + 1; // Customer IDs from 1 to CUSTOMERS
        pthread_create(&customers[i], NULL, customer, (void*)&customerIds[i]);
        sleep(rand() % 2); // Random interval for customers arriving
    }

    // Join customer threads
    for (int i = 0; i < CUSTOMERS; i++) {
        pthread_join(customers[i], NULL);
    }

    // Cleanup semaphores
    sem_destroy(&barberReady);
    sem_destroy(&customerReady);
    sem_destroy(&mutex);

    return 0;
}


/*
./prg4.out
Barber is sleeping
Customer 1 is waiting. Customers waiting: 1
Barber is cutting hair. Customers waiting: 0
Customer 1 is getting a haircut.
Customer 2 is waiting. Customers waiting: 1
Customer 3 is waiting. Customers waiting: 2
Customer 4 is waiting. Customers waiting: 3
Customer 5 leaves because there are no chairs available.
Barber is cutting hair. Customers waiting: 2
Customer 2 is getting a haircut.
Barber is cutting hair. Customers waiting: 1
Customer 3 is getting a haircut.
Barber is cutting hair. Customers waiting: 0
Customer 4 is getting a haircut.


*/
