#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_REQUESTS 100

// Structure to hold disk scheduling requests
struct DSA {
    int request_id;
    int arrival_time_stamp;
    int cylinder;
    int address;
    int process_id;
};

// Function to compare two requests by arrival timestamp
int compareArrival(const void *a, const void *b) {
    struct DSA *reqA = (struct DSA *)a;
    struct DSA *reqB = (struct DSA *)b;
    return reqA->arrival_time_stamp - reqB->arrival_time_stamp;
}

// Function to compare two requests by their cylinder value for SSTF
int compareCylinder(const void *a, const void *b) {
    struct DSA *reqA = (struct DSA *)a;
    struct DSA *reqB = (struct DSA *)b;
    return reqA->cylinder - reqB->cylinder;
}

// FCFS Disk Scheduling
void fcfs(struct DSA requests[], int n) {
    int total_seek_time = 0;
    int current_position = 0;

    printf("\n*** FCFS Disk Scheduling ***\n");
    printf("Request Order: ");
    
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i].cylinder);
        total_seek_time += abs(requests[i].cylinder - current_position);
        current_position = requests[i].cylinder;
    }

    printf("\nTotal Seek Time (FCFS): %d\n", total_seek_time);
}

// SSTF Disk Scheduling
void sstf(struct DSA requests[], int n) {
    bool serviced[MAX_REQUESTS] = {false};
    int total_seek_time = 0;
    int current_position = 0;
    int serviced_count = 0;

    printf("\n*** SSTF Disk Scheduling ***\n");
    while (serviced_count < n) {
        int min_distance = __INT_MAX__;
        int next_request_index = -1;

        // Find the closest request
        for (int i = 0; i < n; i++) {
            if (!serviced[i]) {
                int distance = abs(requests[i].cylinder - current_position);
                if (distance < min_distance) {
                    min_distance = distance;
                    next_request_index = i;
                }
            }
        }

        // Service the closest request
        if (next_request_index != -1) {
            serviced[next_request_index] = true;
            printf("%d ", requests[next_request_index].cylinder);
            total_seek_time += min_distance;
            current_position = requests[next_request_index].cylinder;
            serviced_count++;
        }
    }

    printf("\nTotal Seek Time (SSTF): %d\n", total_seek_time);
}

int main() {
    struct DSA requests[MAX_REQUESTS];
    int n;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter request ID, arrival timestamp, cylinder, address, process ID for request %d:\n", i + 1);
        scanf("%d %d %d %d %d", 
              &requests[i].request_id, 
              &requests[i].arrival_time_stamp,
              &requests[i].cylinder, 
              &requests[i].address, 
              &requests[i].process_id);
    }

    // Sort requests based on arrival time for FCFS
    qsort(requests, n, sizeof(struct DSA), compareArrival);

    // Perform FCFS scheduling
    fcfs(requests, n);

    // Sort requests based on cylinder for SSTF
    qsort(requests, n, sizeof(struct DSA), compareCylinder);

    // Perform SSTF scheduling
    sstf(requests, n);

    return 0;
}

/*
Enter the number of disk requests: 5
Enter request ID, arrival timestamp, cylinder, address, process ID for request 1:
1 0 150 0 1
Enter request ID, arrival timestamp, cylinder, address, process ID for request 2:
2 0 80 0 1
Enter request ID, arrival timestamp, cylinder, address, process ID for request 3:
3 0 50 0 1
Enter request ID, arrival timestamp, cylinder, address, process ID for request 4:
4 0 30 0 1
Enter request ID, arrival timestamp, cylinder, address, process ID for request 5:
5 0 120 0 1

*** FCFS Disk Scheduling ***
Request Order: 150 80 50 30 120 
Total Seek Time (FCFS): 360

*** SSTF Disk Scheduling ***
30 50 80 120 150 
Total Seek Time (SSTF): 150
*/
