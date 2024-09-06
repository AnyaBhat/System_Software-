#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int *sum;
	int n;
	int* seq;
}negaSum;

void* negative_thread(void* param){
	negaSum* data=(negaSum *)param;
	int n= data->n;
	int* sum=data->sum;
	int* seq=data->seq;
	*sum=0;
	for(int i=0;i<n;i++){
		if(seq[i]<0){
			*sum+=seq[i];
		}
	}
	return NULL;
}

int main(){
	int n,sum=0;
	printf("Enter the length of the array:");
	scanf("%d",&n);
	int* seq = (int*)malloc(n * sizeof(int));
	printf("Enter %d elements:",n);
	for(int i=0;i<n;i++){
		scanf("%d",&seq[i]);
	}
    	
   	 
   	negaSum data;
    	data.n=n;
    	data.seq=seq;
    	data.sum=&sum;
    
   	pthread_t thread;
  	pthread_create(&thread,NULL,negative_thread,(void*)&data);
  	pthread_join(thread,NULL);
  	printf("Sum of negative numbers:\n");
     	printf("%d ", sum);
    	printf("\n");
   	free(seq);
    	return EXIT_SUCCESS;
}
/*
$ gcc -o prg2.out prg2.c
$ ./prg2.out
Enter the length of the array:10
Enter 10 elements:-1 -5 8 78 23 12 -6 8 -8 9
Sum of negative numbers:
-20 
*/
