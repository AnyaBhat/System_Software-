#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#define P 5  // Number of processes
#define R 3  // Number of resources

int available[R] = {10, 5, 7};  // Available instances of resources
int maximum[P][R]; // Maximum demand of each process (now user-defined)
int allocation[P][R] = {0}; // Currently allocated resources
int need[P][R]; // Remaining resources needed by each process
pthread_mutex_t lock;

void calculateNeed() {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];
}

bool isSafe() {
    int work[R];
    bool finish[P] = {false};
    for (int i = 0; i < R; i++) work[i] = available[i];

    while (true) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                bool canFinish = true;
                for (int j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    for (int j = 0; j < R; j++) work[j] += allocation[p][j];
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) break;
    }

    for (int i = 0; i < P; i++) {
        if (!finish[i]) return false;
    }
    return true;
}

void *process(void *num) {
    int id = *(int *)num;
    int request[R];

    // Simulate a request
    for (int i = 0; i < R; i++) {
        request[i] = rand() % (need[id][i] + 1);
    }

    pthread_mutex_lock(&lock);
    
    // Print request info
    printf("Process %d requesting: ", id);
    for (int i = 0; i < R; i++) {
        printf("%d ", request[i]);
    }
    printf("\n");

    // Check if request can be granted
    for (int i = 0; i < R; i++) {
        if (request[i] > need[id][i] || request[i] > available[i]) {
            printf("Process %d: Request denied (need or available exceeded).\n", id);
            pthread_mutex_unlock(&lock);
            return NULL; // Request denied
        }
    }

    // Pretend to allocate resources
    for (int i = 0; i < R; i++) {
        available[i] -= request[i];
        allocation[id][i] += request[i];
        need[id][i] -= request[i];
    }

    // Check for safe state
    if (!isSafe()) {
        // Rollback
        for (int i = 0; i < R; i++) {
            available[i] += request[i];
            allocation[id][i] -= request[i];
            need[id][i] += request[i];
        }
        printf("Process %d: Request resulted in unsafe state, rolling back.\n", id);
    } else {
        printf("Process %d: Request granted.\n", id);
    }

    // Print available resources after handling the request
    printf("Available resources after Process %d: ", id);
    for (int i = 0; i < R; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t threads[P];
    int process_ids[P];

    srand(time(NULL)); // Initialize random seed

    // Input maximum demand for each process from the user
    for (int i = 0; i < P; i++) {
        printf("Enter maximum demand for Process %d (3 values): ", i);
        for (int j = 0; j < R; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    calculateNeed();
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < P; i++) {
        process_ids[i] = i;
        pthread_create(&threads[i], NULL, process, &process_ids[i]);
    }

    for (int i = 0; i < P; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}
/*
 ./prg1.out
Enter maximum demand for Process 0 (3 values): 10 5 7
Enter maximum demand for Process 1 (3 values): ^C
$ ./prg1.out
Enter maximum demand for Process 0 (3 values): 7 5 3
Enter maximum demand for Process 1 (3 values): 3 2 2
Enter maximum demand for Process 2 (3 values): 9 0 2
Enter maximum demand for Process 3 (3 values): 2 2 2
Enter maximum demand for Process 4 (3 values): 4 3 3
Process 0 requesting: 4 3 3 
Process 0: Request granted.
Available resources after Process 0: 6 2 4 
Process 1 requesting: 1 0 2 
Process 1: Request granted.
Available resources after Process 1: 5 2 2 
Process 4 requesting: 4 0 2 
Process 4: Request resulted in unsafe state, rolling back.
Available resources after Process 4: 5 2 2 
Process 2 requesting: 3 0 0 
Process 2: Request granted.
Available resources after Process 2: 2 2 2 
Process 3 requesting: 0 2 1 
Process 3: Request granted.
Available resources after Process 3: 2 0 1 

*/
