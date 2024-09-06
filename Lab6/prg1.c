#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int n;
	long long* seq;
}FibData;

void* fib_thread(void* param){
	FibData* data=(FibData *)param;
	int n= data->n;
	long long* seq=data->seq;
	if(n<=0) return NULL;
	seq[0]=0;
	if(n>1) seq[1]=1;
	for(int i=2;i<n;i++){
		seq[i]=seq[i-1]+seq[i-2];
	}
	return NULL;
}

int main(int argc,char* argv[]){
	if (argc != 2) {
       		fprintf(stderr, "Usage: %s <number_of_fibonacci_numbers>\n", argv[0]);
        	return EXIT_FAILURE;
    	}
    	int n=atoi(argv[1]);
    	if(n<=0){
    		fprintf(stderr, "Usage: %s <number_of_fibonacci_numbers>\n", argv[0]);
       		return EXIT_FAILURE;
    	}
   	 long long* seq = (long long*)malloc(n * sizeof(long long));
   	 FibData data;
    	data.n=n;
    	data.seq=seq;
    
   	 pthread_t thread;
  	  pthread_create(&thread,NULL,fib_thread,(void*)&data);
  	  pthread_join(thread,NULL);
  	  printf("Fibonacci sequence:\n");
  	  for (int i = 0; i < n; i++) {
     	   printf("%lld ", seq[i]);
   	 }
    	printf("\n");
   	free(seq);
    	return EXIT_SUCCESS;
}

/*
$ gcc -o prg1.out prg1.c
$ ./prg1.out 10 
Fibonacci sequence:
0 1 1 2 3 5 8 13 21 34 
*/
