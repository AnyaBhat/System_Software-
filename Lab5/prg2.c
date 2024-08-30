#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void main(){
	pid_t pid;
	pid =fork();
	if(pid == -1){
	 	printf("\nERROR child not created");
	 	return;
	}
	else if(pid ==0){
		execlp("./prg1.out", "prg1.out",NULL);
	}
	else{
		wait(NULL);
		printf("Child Completed");
		exit(0);
	}
}
