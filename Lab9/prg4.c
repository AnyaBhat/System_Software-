//This program is partially correct 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    FILE *fp;
    char line[1000];

    // Execute the lsblk command to get detailed information
    fp = popen("lsblk -o NAME,TYPE", "r");
    if (fp == NULL) {
        perror("Failed to run command");
        return 1;
    }

    printf("--Connected Devices--\n");
    printf("%-10s %-10s %-8s\n", "Name", "Type", "Instance");

    // Read the output line by line
    while (fgets(line, sizeof(line), fp) != NULL) {
        // Check if the line is not empty and is not the header
        if (strlen(line) > 1 && strncmp(line, "NAME", 4) != 0) {
            char name[100], type[100];
            int instance = 0; // Default to 0 for non-partitions

            // Parse the line into variables
            sscanf(line, "%s %s", name, type);

            // Calculate instance number from device name
            if (strncmp(name, "loop", 4) != 0) { // Skip loop devices for simplicity
                // Check if the name has a partition number
                char *p = name;
                while (*p) {
                    // Check for the last digit in the name
                    if (isdigit(*p)) {
                        instance = *p - '0'; // Convert character to integer
                    }
                    p++;
                }
            }

            // Print the information with formatted output
            printf("%-10s %-10s %-8d\n", name, type, instance);
        }
    }

    // Close the process
    pclose(fp);

    return 0;
}


/*
Output got
 ./prg4.out
--Connected Devices--
Name       Type       Instance
sda        disk       0       
├─sda1 part       1       
├─sda2 part       2       
└─sda3 part       3       
nvme0n1    disk       1       
├─nvme0n1p1 part       1       
├─nvme0n1p2 part       2       
├─nvme0n1p3 part       3       
├─nvme0n1p4 part       4       
└─nvme0n1p5 part       5   



Expected output 
--Connected Devices--
Name       Type       Instance
sda        disk       0       
├─sda1     part       1       
├─sda2     part       2       
└─sda3     part       3       
nvme0n1    disk       0       
├─nvme0n1p1 part       1       
├─nvme0n1p2 part       2       
├─nvme0n1p3 part       3       
├─nvme0n1p4 part       4       
└─nvme0n1p5 part       5       

*/
