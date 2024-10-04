#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DISK_SIZE 20       // Total disk blocks
#define SPARE_BLOCKS 5     // Number of spare blocks
#define MAX_FILES 10       // Maximum number of files

typedef struct {
    int block_number;
    int spare_block_number;
} BadBlockEntry;

typedef struct {
    char name[20];
    int start_block;
    int size; // Number of blocks allocated
} File;

typedef struct {
    File files[MAX_FILES];
    int file_count;
    int bad_blocks[DISK_SIZE];
    BadBlockEntry bad_block_table[DISK_SIZE];
} FileSystem;

// Function declarations
void initialize_file_system(FileSystem* fs);
int allocate_file(FileSystem* fs, const char* name, int size);
void mark_block_as_bad(FileSystem* fs, int block_number);
int access_file(FileSystem* fs, const char* name);
void print_file_system(const FileSystem* fs);

// Main function
int main() {
    FileSystem fs;
    initialize_file_system(&fs);

    allocate_file(&fs, "file1.txt", 5);
    allocate_file(&fs, "file2.txt", 3);
    mark_block_as_bad(&fs, 2);
    allocate_file(&fs, "file3.txt", 4);

    print_file_system(&fs);

    access_file(&fs, "file1.txt");
    access_file(&fs, "file2.txt");
    access_file(&fs, "file3.txt");

    return 0;
}

// Function implementations
void initialize_file_system(FileSystem* fs) {
    fs->file_count = 0;
    memset(fs->bad_blocks, 0, sizeof(fs->bad_blocks));
    memset(fs->bad_block_table, -1, sizeof(fs->bad_block_table));
}

int allocate_file(FileSystem* fs, const char* name, int size) {
    if (fs->file_count >= MAX_FILES) {
        printf("Cannot allocate more files. Maximum limit reached.\n");
        return -1;
    }

    // Find contiguous free blocks
    int start_block = -1;
    for (int i = 0; i < DISK_SIZE - size + 1; i++) {
        int found = 1;
        for (int j = 0; j < size; j++) {
            if (fs->bad_blocks[i + j] || (fs->bad_block_table[i + j].block_number != -1)) {
                found = 0;
                break;
            }
        }
        if (found) {
            start_block = i;
            break;
        }
    }

    if (start_block == -1) {
        printf("Not enough contiguous space for file %s\n", name);
        return -1;
    }

    // Allocate the file
    strcpy(fs->files[fs->file_count].name, name);
    fs->files[fs->file_count].start_block = start_block;
    fs->files[fs->file_count].size = size;

    // Mark blocks as allocated
    for (int i = 0; i < size; i++) {
        fs->bad_blocks[start_block + i] = 1;
    }

    fs->file_count++;
    printf("Allocated %s at block %d (size: %d)\n", name, start_block, size);
    return 0;
}

void mark_block_as_bad(FileSystem* fs, int block_number) {
    if (block_number < 0 || block_number >= DISK_SIZE) {
        printf("Invalid block number.\n");
        return;
    }

    // Mark the block as bad
    fs->bad_blocks[block_number] = 1;
    printf("Marked block %d as bad.\n", block_number);

    // Record bad block in the bad blocks table
    for (int i = 0; i < DISK_SIZE; i++) {
        if (fs->bad_block_table[i].block_number == -1) {
            fs->bad_block_table[i].block_number = block_number;
            fs->bad_block_table[i].spare_block_number = block_number + SPARE_BLOCKS; // Simple allocation for spare
            printf("Assigned spare block %d for bad block %d\n", fs->bad_block_table[i].spare_block_number, block_number);
            break;
        }
    }
}

int access_file(FileSystem* fs, const char* name) {
    for (int i = 0; i < fs->file_count; i++) {
        if (strcmp(fs->files[i].name, name) == 0) {
            printf("Accessing file %s at block %d (size: %d)\n", name, fs->files[i].start_block, fs->files[i].size);
            return 0;
        }
    }
    printf("File %s not found.\n", name);
    return -1;
}

void print_file_system(const FileSystem* fs) {
    printf("\nFile System State:\n");
    for (int i = 0; i < fs->file_count; i++) {
        printf("File: %s, Start Block: %d, Size: %d\n", fs->files[i].name, fs->files[i].start_block, fs->files[i].size);
    }

    printf("\nBad Blocks Table:\n");
    for (int i = 0; i < DISK_SIZE; i++) {
        if (fs->bad_block_table[i].block_number != -1) {
            printf("Bad Block: %d, Spare Block: %d\n", fs->bad_block_table[i].block_number, fs->bad_block_table[i].spare_block_number);
        }
    }
}


/*
./prg3.out
Allocated file1.txt at block 0 (size: 5)
Allocated file2.txt at block 5 (size: 3)
Marked block 2 as bad.
Assigned spare block 7 for bad block 2
Allocated file3.txt at block 8 (size: 4)

File System State:
File: file1.txt, Start Block: 0, Size: 5
File: file2.txt, Start Block: 5, Size: 3
File: file3.txt, Start Block: 8, Size: 4

Bad Blocks Table:
Bad Block: 2, Spare Block: 7
Accessing file file1.txt at block 0 (size: 5)
Accessing file file2.txt at block 5 (size: 3)
Accessing file file3.txt at block 8 (size: 4)
*/

