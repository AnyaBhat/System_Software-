#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h> 

void main(){
	int status;
	pid_t pid;
	pid=fork();
	if(pid == -1){
	 	printf("\nERROR child not created");
	 	return;
	}
	else if(pid ==0){
		printf("\n I'm the child process!");
		sleep(10);
		printf("\n Child process %d completed",getpid());
		exit(EXIT_SUCCESS);
	}
	else{
		wait(&status);
		printf("\n I'm the parent!");
		printf("\n Child returned:%d\n",status);
	}
}
