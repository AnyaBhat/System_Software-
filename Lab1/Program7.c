#include <stdio.h>

int main() {
    long i, j;
    for (i = 0; i < 100000; i++) {
        for (j = 0; j < 100000; j++) {
            // Just a placeholder operation
            int dummy = i * j;
        }
    }
    printf("Nested loops completed.\n");
    return 0;
}

// gcc nested_loops.c -o nested_loops
// ./nested_loops &
// ps -ef | grep nested_loops
// kill <PID>
