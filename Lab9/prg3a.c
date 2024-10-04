//asks for user input 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_BLOCKS 100
#define MAX_BAD_BLOCKS 10

// Structure to represent a bad block
struct BadBlock {
    int bad_block;
    int spare_block;
};

// Function to print the file system state
void printFileSystemState(int blocks[], int n, struct BadBlock bad_blocks[], int bad_count) {
    printf("\nFile System State:\n");
    for (int i = 0; i < n; i++) {
        if (blocks[i] == -1) {
            printf("Block %d: BAD BLOCK\n", i);
        } else {
            printf("Block %d: File ID %d\n", i, blocks[i]);
        }
    }

    printf("\nBad Blocks Table:\n");
    for (int i = 0; i < bad_count; i++) {
        printf("Bad Block: %d, Spare Block: %d\n", bad_blocks[i].bad_block, bad_blocks[i].spare_block);
    }
}

int main() {
    int n, m;
    int blocks[MAX_BLOCKS];
    struct BadBlock bad_blocks[MAX_BAD_BLOCKS];
    int bad_count = 0;

    // Initialize the blocks array
    for (int i = 0; i < MAX_BLOCKS; i++) {
        blocks[i] = -1; // -1 indicates a free block
    }

    printf("Enter the number of blocks in the file system: ");
    scanf("%d", &n);
    printf("Enter the number of spare blocks: ");
    scanf("%d", &m);

    // Fill the file system with file IDs
    for (int i = 0; i < n; i++) {
        printf("Enter file ID for block %d: ", i);
        scanf("%d", &blocks[i]);
    }

    // Mark spare blocks as free
    for (int i = n; i < n + m; i++) {
        blocks[i] = -1; // Initialize spare blocks
    }

    // Simulate bad blocks
    int bad_block_index;
    while (bad_count < MAX_BAD_BLOCKS) {
        printf("Enter the index of a bad block (-1 to stop): ");
        scanf("%d", &bad_block_index);
        if (bad_block_index == -1) break;

        // Check if the block is valid and marked as good
        if (bad_block_index < 0 || bad_block_index >= n || blocks[bad_block_index] == -1) {
            printf("Invalid or already marked as BAD BLOCK. Try again.\n");
            continue;
        }

        // Find a spare block
        bool spare_found = false;
        for (int j = n; j < n + m; j++) {
            if (blocks[j] == -1) { // Free block found
                blocks[j] = blocks[bad_block_index]; // Allocate spare block
                bad_blocks[bad_count].bad_block = bad_block_index;
                bad_blocks[bad_count].spare_block = j;
                bad_count++;
                blocks[bad_block_index] = -1; // Mark the original block as bad
                printf("Bad Block %d replaced with Spare Block %d.\n", bad_block_index, j);
                spare_found = true;
                break;
            }
        }

        if (!spare_found) {
            printf("No spare blocks available.\n");
        }
    }

    // Print the final state of the file system
    printFileSystemState(blocks, n + m, bad_blocks, bad_count);

    return 0;
}


/*
./prg3a.out
Enter the number of blocks in the file system: 5
Enter the number of spare blocks: 3
Enter file ID for block 0: 89
Enter file ID for block 1: 25
Enter file ID for block 2: 42
Enter file ID for block 3: 12
Enter file ID for block 4: 78
Enter the index of a bad block (-1 to stop): 1
Bad Block 1 replaced with Spare Block 5.
Enter the index of a bad block (-1 to stop): 3
Bad Block 3 replaced with Spare Block 6.
Enter the index of a bad block (-1 to stop): 0
Bad Block 0 replaced with Spare Block 7.
Enter the index of a bad block (-1 to stop): 2
No spare blocks available.
Enter the index of a bad block (-1 to stop): -1

File System State:
Block 0: BAD BLOCK
Block 1: BAD BLOCK
Block 2: File ID 42
Block 3: BAD BLOCK
Block 4: File ID 78
Block 5: File ID 25
Block 6: File ID 12
Block 7: File ID 89

Bad Blocks Table:
Bad Block: 1, Spare Block: 5
Bad Block: 3, Spare Block: 6
Bad Block: 0, Spare Block: 7
*/
