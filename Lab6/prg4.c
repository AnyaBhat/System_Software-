#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int size;
    int *result;
    int is_even; // 1 for even, 0 for odd
} ThreadData;

void* sum_thread(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int *arr = data->arr;
    int size = data->size;
    int *result = data->result;
    int is_even = data->is_even;
    
    *result = 0; // Initialize the result to 0
    for (int i = 0; i < size; i++) {
        if ((arr[i] % 2 == 0 && is_even) || (arr[i] % 2 != 0 && !is_even)) {
            *result += arr[i];
        }
    }
    
    return NULL;
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
$ gcc -o prg4.out prg4.c
$ chmod +x prg4.out 
$ ./prg4.out 
Enter the number of elements: 10
Enter 10 elements: 1 2 3 4 5 6 7 8 9 10
Sum of even numbers: 30
Sum of odd numbers: 25

    pthread_t even_thread, odd_thread;
    int even_sum = 0, odd_sum = 0;
    
    ThreadData even_data = {arr, n, &even_sum, 1};
    ThreadData odd_data = {arr, n, &odd_sum, 0};

    pthread_create(&even_thread, NULL, sum_thread, (void*)&even_data); 
    pthread_create(&odd_thread, NULL, sum_thread, (void*)&odd_data) ;

   pthread_join(even_thread, NULL);
   pthread_join(odd_thread, NULL) ;

    // Print the results
    printf("Sum of even numbers: %d\n", even_sum);
    printf("Sum of odd numbers: %d\n", odd_sum);

    free(arr);
    return EXIT_SUCCESS;
}

/*
gcc -o prg4.out prg4.c
$ chmod +x prg4.out 
$ ./prg4.out 
Enter the number of elements: 10
Enter 10 elements: 1 2 3 4 5 6 7 8 9 10
Sum of even numbers: 30
Sum of odd numbers: 25

*/
