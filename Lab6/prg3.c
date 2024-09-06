#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>

#define NUM_THREADS 4 

typedef struct{
	int start;
	int end;
}prime;

bool isPrime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

void* prime_thread(void* param){
	prime* data=(prime *)param;
	int start= data->start;
	int end=data->end;
    	for(int i=start;i<=end;i++){
    		if (isPrime(i)) {
    			printf("%d is a prime number.\n", i);
        	}
    	}
    	pthread_exit(NULL);
}

int main(){
	int range,segment,remainder;
	int start, end;
	
	printf("Enter the start number:");
	scanf("%d",&start);
	printf("Enter the end number:");
	scanf("%d",&end);
	
	range=end-start+1;
	segment=range/NUM_THREADS;
	remainder=range%NUM_THREADS;
	
	
   	pthread_t thread[NUM_THREADS];
   	prime data[NUM_THREADS];
   	
   	for (int i = 0; i < NUM_THREADS; i++) {
    		data[i].start=start+i*segment;
    		data[i].end=start+(i+1)*segment-1;
    		if (i == NUM_THREADS - 1) {
            		data[i].end += remainder;
        	}
	  	pthread_create(&thread[i],NULL,prime_thread,(void*)&data[i]);
        }
        
        for (int i = 0; i < NUM_THREADS; i++) {
  		pthread_join(thread[i],NULL);
	}
	
    	return EXIT_SUCCESS;
}
/*
$ ./prg3.out
Enter the start number:5
Enter the end number:10
5 is a prime number.
7 is a prime number.

*/
