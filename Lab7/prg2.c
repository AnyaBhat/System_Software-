#include <stdio.h>
#include <stdlib.h>

#define TIME_QUANTUM_Q1 5
#define TIME_QUANTUM_Q2 8

typedef struct Process {
    int id;
    int burst_time; // Total time needed for the process to complete
    struct Process* next;
} Process;

typedef struct Queue {
    Process* front;
    Process* rear;
    int size;
} Queue;


// Create a new empty queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

// Enqueue a process into the queue
void enqueue(Queue* q, int id, int burst_time) {
    Process* new_process = (Process*)malloc(sizeof(Process));
    new_process->id = id;
    new_process->burst_time = burst_time;
    new_process->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = new_process;
    } else {
        q->rear->next = new_process;
        q->rear = new_process;
    }
    q->size++;
}

// Check if the queue is empty
int isEmpty(Queue* q) {
    return q->size == 0;
}

// Dequeue a process from the queue
Process* dequeue(Queue* q) {
    if (isEmpty(q)) {
        return NULL;
    }

    Process* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    q->size--;

    return temp;
}


// Round Robin scheduling for a queue
void roundRobin(Queue* src_q, Queue* dest_q, int time_quantum) {
    if (isEmpty(src_q)) return;

    Process* p = dequeue(src_q);
    printf("Process %d with burst time %d\n", p->id, p->burst_time);
    if (p->burst_time > time_quantum) {
        p->burst_time -= time_quantum;
        enqueue(dest_q, p->id, p->burst_time);
    } else {
        printf("Process %d completed.\n", p->id);
        free(p);
    }
}

// FCFS scheduling for a queue
void fcfs(Queue* src_q, Queue* dest_q) {
    if (isEmpty(src_q)) return;

    Process* p = dequeue(src_q);
    printf("Process %d with burst time %d\n", p->id, p->burst_time);
    // Processes in Q3 (FCFS) are executed completely
    if (p->burst_time > TIME_QUANTUM_Q2) {
        p->burst_time -= TIME_QUANTUM_Q2;
        enqueue(dest_q, p->id, p->burst_time);
    } else {
        printf("Process %d completed.\n", p->id);
        free(p);
    }
}

int main() {
    Queue* q1 = createQueue(); // Round Robin with time quantum 5
    Queue* q2 = createQueue(); // Round Robin with time quantum 8
    Queue* q3 = createQueue(); // First Come First Serve

    // Adding some processes to Q1 for testing
    enqueue(q1, 1, 10);
    enqueue(q1, 2, 15);
    enqueue(q1, 3, 20);

    // Simulating the scheduler
    while (!isEmpty(q1) || !isEmpty(q2) || !isEmpty(q3)) {
        if (!isEmpty(q1)) {
            printf("Executing Q1 (RR5):\n");
            roundRobin(q1, q2, TIME_QUANTUM_Q1);
        }
        
        if (!isEmpty(q2)) {
            printf("Executing Q2 (RR8):\n");
            roundRobin(q2, q3, TIME_QUANTUM_Q2);
        }
        
        if (!isEmpty(q3)) {
            printf("Executing Q3 (FCFS):\n");
            fcfs(q3, q2);
        }
    }

    // Clean up
    free(q1);
    free(q2);
    free(q3);

    return 0;
}

/*
./prg2.out
Executing Q1 (RR5):
Process 1 with burst time 10
Executing Q2 (RR8):
Process 1 with burst time 5
Process 1 completed.
Executing Q1 (RR5):
Process 2 with burst time 15
Executing Q2 (RR8):
Process 2 with burst time 10
Executing Q3 (FCFS):
Process 2 with burst time 2
Process 2 completed.
Executing Q1 (RR5):
Process 3 with burst time 20
Executing Q2 (RR8):
Process 3 with burst time 15
Executing Q3 (FCFS):
Process 3 with burst time 7
Process 3 completed.
*/

