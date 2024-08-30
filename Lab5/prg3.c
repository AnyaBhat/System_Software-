#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void main(){
	pid_t pid;
	pid= fork();
	
	if(pid==-1){
		printf("ERROR child not created");
		return;
	}else if(pid ==0){
		printf("Child Process!!!\n");
		printf("Child PID:%d\n",getpid());
		printf("Parent PPID:%d\n",getppid());
		exit(EXIT_SUCCESS);			
	}else{
		printf("Parent Process!!!\n");
		printf("Parent PID:%d\n",getpid());
		printf("Child PID:%d\n",pid);
		exit(EXIT_SUCCESS);		
	}
	return;
}
