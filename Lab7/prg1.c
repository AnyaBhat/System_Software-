#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define A_MEGABYTE (1024 * 1024)

// Define the memory block structure
typedef struct mab {
    int offset;            // Starting address of the block (for demonstration)
    int size;              // Size of the block
    int allocated;         // Allocation status (0 = free, 1 = allocated)
    struct mab *next;      // Pointer to the next block
    struct mab *prev;      // Pointer to the previous block
} Mab;

typedef Mab* MabPtr;

// Create a new block of memory
MabPtr createBlock(int offset, int size, int allocated) {
    MabPtr block = (MabPtr)malloc(sizeof(Mab));
    block->offset = offset;
    block->size = size;
    block->allocated = allocated;
    block->next = NULL;
    block->prev = NULL;
    return block;
}

// Print memory blocks for debugging
void printMemory(MabPtr head) {
    MabPtr temp = head;
    while (temp) {
        printf("Offset: %d, Size: %d, Allocated: %d\n", temp->offset, temp->size, temp->allocated);
        temp = temp->next;
    }
}

// Check if memory of the given size is available
MabPtr memChk(MabPtr m, int size) {
    while (m) {
        if (!m->allocated && m->size >= size) {
            return m;
        }
        m = m->next;
    }
    return NULL;
}

// Allocate memory block using the given policy
MabPtr memAlloc(MabPtr m, int size, int policy) {
    MabPtr best = NULL, fitBlock = NULL;
    int bestFitSize = INT_MAX;

    while (m) {
        if (!m->allocated && m->size >= size) {
            if (policy == 1) { // First Fit
                fitBlock = m;
                break;
            } else if (policy == 2) { // Best Fit
                if (m->size < bestFitSize) {
                    bestFitSize = m->size;
                    fitBlock = m;
                }
            } else if (policy == 3) { // Worst Fit
                if (m->size > bestFitSize) {
                    bestFitSize = m->size;
                    fitBlock = m;
                }
            }
        }
        m = m->next;
    }

    if (fitBlock) {
        fitBlock->allocated = 1;
        if (fitBlock->size > size) {
            // Split the block
            MabPtr newBlock = createBlock(fitBlock->offset + size, fitBlock->size - size, 0);
            newBlock->next = fitBlock->next;
            if (fitBlock->next) fitBlock->next->prev = newBlock;
            newBlock->prev = fitBlock;
            fitBlock->next = newBlock;
            fitBlock->size = size;
        }
        return fitBlock;
    }
    return NULL;
}

// Free a memory block and merge adjacent free blocks
MabPtr memFree(MabPtr m) {
    if (!m || !m->allocated) return m;
    m->allocated = 0;
    
    // Merge with adjacent free blocks
    if (m->prev && !m->prev->allocated) {
        m->prev->size += m->size;
        m->prev->next = m->next;
        if (m->next) m->next->prev = m->prev;
        free(m);
        m = m->prev;
    }
    if (m->next && !m->next->allocated) {
        m->size += m->next->size;
        MabPtr temp = m->next;
        m->next = m->next->next;
        if (m->next) m->next->prev = m;
        free(temp);
    }
    return m;
}

// Merge two adjacent free memory blocks
MabPtr memMerge(MabPtr m) {
    // Assumes m is free
    if (m->prev && !m->prev->allocated) {
        m->prev->size += m->size;
        m->prev->next = m->next;
        if (m->next) m->next->prev = m->prev;
        free(m);
        m = m->prev;
    }
    if (m->next && !m->next->allocated) {
        m->size += m->next->size;
        MabPtr temp = m->next;
        m->next = m->next->next;
        if (m->next) m->next->prev = m;
        free(temp);
    }
    return m;
}

// Split a memory block into allocated and free parts
MabPtr memSplit(MabPtr m, int size) {
    if (m->size > size) {
        MabPtr newBlock = createBlock(m->offset + size, m->size - size, 0);
        newBlock->next = m->next;
        if (m->next) m->next->prev = newBlock;
        newBlock->prev = m;
        m->next = newBlock;
        m->size = size;
    }
    return m;
}

int main() {
    // Create initial memory blocks
    MabPtr head = createBlock(0, 100, 0);
    head->next = createBlock(100, 200, 0);
    head->next->prev = head;
    head->next->next = createBlock(300, 50, 0);
    head->next->next->prev = head->next;

    printMemory(head);

    // Allocate memory
    MabPtr allocated = memAlloc(head, 100, 2); // First Fit
    if (allocated) printf("Allocated 300 units of memory\n");
    printMemory(head);

    // Free memory
    MabPtr freed = memFree(allocated);
    if (freed) printf("Freed memory\n");
    printMemory(head);

    return 0;
}

