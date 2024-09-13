#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

typedef struct {
    int page_number;
    int referenced; // Reference bit
} PageFrame;

void print_frame_state(PageFrame frames[], int num_frames) {
    printf("Frames: ");
    for (int i = 0; i < num_frames; i++) {
        if (frames[i].referenced)
            printf("[%d*] ", frames[i].page_number);
        else
            printf("[%d ] ", frames[i].page_number);
    }
    printf("\n");
}

int second_chance(int pages[], int num_pages, int num_frames) {
    PageFrame frames[MAX_FRAMES];
    int page_faults = 0;
    int pointer = 0; // Points to the next frame to be checked

    // Initialize frames
    for (int i = 0; i < num_frames; i++) {
        frames[i].page_number = -1;
        frames[i].referenced = 0;
    }

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        int page_found = 0;

        // Check if the page is already in one of the frames
        for (int j = 0; j < num_frames; j++) {
            if (frames[j].page_number == page) {
                frames[j].referenced = 1; // Page is referenced
                page_found = 1;
                break;
            }
        }

        if (page_found) {
            // Page hit, no need to replace
            printf("Page %d hit\n", page);
            continue;
        }

        // Page fault, need to replace a page
        printf("Page %d fault\n", page);

        // Find a frame to replace
        while (frames[pointer].referenced) {
            frames[pointer].referenced = 0; // Give a second chance
            pointer = (pointer + 1) % num_frames;
        }

        // Replace the page
        frames[pointer].page_number = page;
        frames[pointer].referenced = 1; // New page is referenced
        pointer = (pointer + 1) % num_frames;

        page_faults++;
        print_frame_state(frames, num_frames);
    }

    return page_faults;
}

int main() {
    int pages[MAX_PAGES];
    int num_pages, num_frames;

    // Input number of pages and number of frames
    printf("Enter the number of pages: ");
    scanf("%d", &num_pages);

    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);

    if (num_frames > MAX_FRAMES || num_pages > MAX_PAGES) {
        printf("Number of pages or frames exceeds the limit.\n");
        return 1;
    }

    printf("Enter the page reference string:\n");
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &pages[i]);
    }

    int page_faults = second_chance(pages, num_pages, num_frames);
    float hit_ratio = 1.0 - (float)page_faults / num_pages;

    printf("Total number of page faults: %d\n", page_faults);
    printf("Hit ratio: %.2f\n", hit_ratio);

    return 0;
}

/*
Enter the number of pages: 15
Enter the number of frames: 4
Enter the page reference string:
7 0 1 2 0 3 0 4 2 3 0 3 2 3 4
Page 7 fault
Frames: [7*] [-1 ] [-1 ] [-1 ] 
Page 0 fault
Frames: [7*] [0*] [-1 ] [-1 ] 
Page 1 fault
Frames: [7*] [0*] [1*] [-1 ] 
Page 2 fault
Frames: [7*] [0*] [1*] [2*] 
Page 0 hit
Page 3 fault
Frames: [3*] [0 ] [1 ] [2 ] 
Page 0 hit
Page 4 fault
Frames: [3*] [0 ] [4*] [2 ] 
Page 2 hit
Page 3 hit
Page 0 hit
Page 3 hit
Page 2 hit
Page 3 hit
Page 4 hit
Total number of page faults: 6
Hit ratio: 0.60
*/
