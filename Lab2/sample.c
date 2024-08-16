// Simple C program to display "Hello World"

// Header file for input output functions
#include <stdio.h>

// Main function: entry point for execution
int main() {
	long i,j;
	for(i=0;i<100000;i++){
		for(j=0;j<100000;j++){
			int dummy=i*j;
		}
	}
	printf("Hello World");

    return 0;
}

