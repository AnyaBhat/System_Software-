#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct mab {
    int offset;            // Starting address of the block
    int size;              // Size of the block
    int allocated;         // Allocation status (0 = free, 1 = allocated)
    struct mab *next;      // Pointer to the next block
    struct mab *prev;      // Pointer to the previous block
} Mab;

typedef Mab* MabPtr;


MabPtr memChk(MabPtr m, int size) {
    while (m) {
        if (!m->allocated && m->size >= size) {
            return m;
        }
        m = m->next;
    }
    return NULL;
}

MabPtr memSplit(MabPtr m, int size) {
    if (m->size > size) {
        MabPtr newBlock = (MabPtr)malloc(sizeof(Mab));
        newBlock->offset = m->offset + size;
        newBlock->size = m->size - size;
        newBlock->allocated = 0;
        newBlock->next = m->next;
        newBlock->prev = m;
        if (m->next) m->next->prev = newBlock;
        m->next = newBlock;
        m->size = size;
    }
    return m;
}

MabPtr memAlloc(MabPtr m, int size, int policy) {
    MabPtr bestFit = NULL;
    int bestFitSize = INT_MAX;

    while (m) {
        if (!m->allocated && m->size >= size) {
            if (policy == 1) { // First Fit
                m->allocated = 1;
                if (m->size > size) {
                    // Split the block
                    memSplit(m, size);
                }
                return m;
            } else if (policy == 2) { // Best Fit
                if (m->size < bestFitSize) {
                    bestFitSize = m->size;
                    bestFit = m;
                }
            } else if (policy == 3) { // Worst Fit
                if (m->size > bestFitSize) {
                    bestFitSize = m->size;
                    bestFit = m;
                }
            }
        }
        m = m->next;
    }

    if ((policy == 2 || policy == 3) && bestFit) {
        bestFit->allocated = 1;
        if (bestFit->size > size) {
            // Split the block
            memSplit(bestFit, size);
        }
        return bestFit;
    }
    return NULL;
}

MabPtr memMerge(MabPtr m) {
    if (!m) return NULL;
    
    // Merge with previous block if free
    if (m->prev && !m->prev->allocated) {
        m->prev->size += m->size;
        m->prev->next = m->next;
        if (m->next) m->next->prev = m->prev;
        free(m);
        m = m->prev;
    }
    
    // Merge with next block if free
    if (m->next && !m->next->allocated) {
        m->size += m->next->size;
        MabPtr temp = m->next;
        m->next = m->next->next;
        if (m->next) m->next->prev = m;
        free(temp);
    }
    
    return m;
}

MabPtr memFree(MabPtr m) {
    if (!m || !m->allocated) return m;
    m->allocated = 0;
    return memMerge(m);
}



// Print memory blocks
    void printMemory(MabPtr head) {
        while (head) {
            printf("Offset: %d, Size: %d, Allocated: %d\n", head->offset, head->size, head->allocated);
            head = head->next;
        }
    }
    
int main() {
    // Create initial memory blocks
    MabPtr head = (MabPtr)malloc(sizeof(Mab));
    head->offset = 0;
    head->size = 100;
    head->allocated = 0;
    head->next = (MabPtr)malloc(sizeof(Mab));
    head->next->prev = head;
    head->next->offset = 100;
    head->next->size = 200;
    head->next->allocated = 0;
    head->next->next = (MabPtr)malloc(sizeof(Mab));
    head->next->next->prev = head->next;
    head->next->next->offset = 300;
    head->next->next->size = 50;
    head->next->next->allocated = 0;
    head->next->next->next = NULL;
    printMemory(head);

    // Allocate memory (First Fit)
    MabPtr allocated = memAlloc(head, 30, 1); // First Fit
    if (allocated) printf("Allocated 30 units of memory\n");
    printMemory(head);

    // Free memory
    MabPtr freed = memFree(allocated);
    if (freed) printf("Freed memory\n");
    printMemory(head);

    return 0;
}
