#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt;
int readcount = 0;
int data = 0;

void *reader(void *arg)
{
    int n=2;
    while(n)
    {
        sem_wait(&mutex);
        readcount++;
        if (readcount == 1)
        {
            sem_wait(&wrt);
        }
        sem_post(&mutex);

        printf("Reader %d reads: %d\n", *((int *)arg), data);

        sem_wait(&mutex);
        readcount--;
        if (readcount == 0)
        {
            sem_post(&wrt);
        }
        sem_post(&mutex);
        usleep(1100000);
        n--;
    }
}

void *writer(void *arg)
{
    int n=2;
    while(n)
    {
        sem_wait(&wrt);
        data++;
        printf("Writer %d writes: %d\n", *((int *)arg), data);
        sem_post(&wrt);
        usleep(1000000);
        n--;
    }
}

int main()
{
    int i;
    pthread_t read_thread[5], write_thread[5];
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    int rval[5], wval[5];
    for (i = 0; i < 5; i++)
    {
        rval[i] = i + 1;
        wval[i] = i + 1;
        pthread_create(&read_thread[i], NULL, reader, &rval[i]);
        pthread_create(&write_thread[i], NULL, writer, &wval[i]);
    }

    for (i = 0; i < 5; i++)
    {
        pthread_join(read_thread[i], NULL);
        pthread_join(write_thread[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}




/*
 ./prg2.out
Reader 3 reads: 0
Reader 5 reads: 0
Reader 2 reads: 0
Reader 1 reads: 0
Reader 4 reads: 0
Writer 1 writes: 1
Writer 4 writes: 2
Writer 2 writes: 3
Writer 3 writes: 4
Writer 5 writes: 5
Writer 1 writes: 6
Writer 5 writes: 7
Writer 3 writes: 8
Writer 2 writes: 9
Writer 4 writes: 10
Reader 3 reads: 10
Reader 5 reads: 10
Reader 2 reads: 10
Reader 1 reads: 10
Reader 4 reads: 10
*/
