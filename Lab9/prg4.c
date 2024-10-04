#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
                    if (*p >= '0' && *p <= '9') {
                        instance = atoi(p); // Convert the number part to integer
                        break; // Found the first digit, exit the loop
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

