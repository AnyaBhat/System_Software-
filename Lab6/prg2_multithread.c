#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4 

typedef struct{
	int *sum;
   	int start;
    	int end;
    	int *seq;
}negaSum;

void* negative_thread(void* param){
	negaSum* data=(negaSum *)param;
	int *sum = data->sum;
    	int start = data->start;
    	int end = data->end;
    	int *seq = data->seq;

    	int local_sum = 0;
    	for (int i = start; i <= end; i++) {
        	if (seq[i] < 0) {
            		local_sum += seq[i];
        	}
   	 }

    	// Use atomic operations to safely update the global sum
   	 __sync_fetch_and_add(sum, local_sum);
	
   	 return NULL;
}

int main(){
	int n,total_sum = 0;
	printf("Enter the length of the array:");
	scanf("%d",&n);
	int* seq = (int*)malloc(n * sizeof(int));
	printf("Enter %d elements:",n);
	for(int i=0;i<n;i++){
		scanf("%d",&seq[i]);
	}
    	
   	pthread_t thread[NUM_THREADS];
   	 
   	negaSum data[NUM_THREADS];
   	int chunk_size = n / NUM_THREADS;
   	int remainder = n % NUM_THREADS;
   	
    	for (int i = 0; i < NUM_THREADS; i++) {
        	data[i].seq = seq;
        	data[i].start = i * chunk_size;
        	data[i].end = (i == NUM_THREADS - 1) ? (i + 1) * chunk_size + remainder - 1 : (i + 1) * chunk_size - 1;
        	data[i].sum = &total_sum;
    
  		pthread_create(&thread[i],NULL,negative_thread,(void*)&data[i]);
  	}
  	
  	for (int i = 0; i < NUM_THREADS; i++) {
	  	pthread_join(thread[i],NULL);
  	}
  	
  	 printf("Sum of negative numbers: %d\n", total_sum);
    	
   	free(seq);
    	return EXIT_SUCCESS;
}
/*
$ gcc -o prg2.out prg2.c
$ ./prg2.out
Enter the length of the array:10
Enter 10 elements:-1 -5 8 78 23 12 -6 8 -8 9
Sum of negative numbers: -20

*/
