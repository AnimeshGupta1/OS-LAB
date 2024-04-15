#include<stdio.h>

int frames_count, references_count, page_faults = 0;
int ref[50], frames[50], recent[10], lru_calculations[50];

// Function to get the victim page using LRU
int get_lru_victim();

int main() {
    printf("\n\t\t\t LRU PAGE REPLACEMENT ALGORITHM");

    // Input number of frames and reference string
    printf("\nEnter the number of frames: ");
    scanf("%d", &frames_count);
    printf("Enter the size of reference string: ");
    scanf("%d", &references_count);
    printf("Enter the reference string (separated by space): ");
    for (int i = 0; i < references_count; i++) 
        scanf("%d", &ref[i]);

    // Initialize arrays
    for (int i = 1; i <= frames_count; i++) {
        frames[i] = -1;
        lru_calculations[i] = 0;
    }

    for (int i = 0; i < 10; i++) 
        recent[i] = 0;

    // Process the reference string
    printf("\n\n\t\t LRU PAGE REPLACEMENT ALGORITHM\n");
    printf("\nReference String\t\tPage Frames\n");

    for (int i = 0; i < references_count; i++) {
        int flag = 0;
        printf("\n\t %d\t \t \t \t ", ref[i]);

        // Check if page already in frames
        for (int j = 0; j < frames_count; j++) {
            if (frames[j] == ref[i]) {
                flag = 1;
                break;
            }
        }

        // Page fault handling
        if (flag == 0) {
            page_faults++;

            // Find victim page using LRU
            int victim = get_lru_victim();
            frames[victim] = ref[i];

            // Update recent array
            recent[ref[i]] = i;

            // Display current page frames
            for (int j = 0; j < frames_count; j++) 
                printf("%4d", frames[j]);
        }
    }

    // Print total number of page faults
    printf("\n\n\t No. of page faults: %d\n", page_faults);
    return 0;
}

// Function to get the victim page using LRU
int get_lru_victim() {
    int temp1, temp2;
    
    // Calculate LRU for each frame
    for (int i = 0; i < frames_count; i++) {
        temp1 = frames[i];
        lru_calculations[i] = recent[temp1];
    }

    // Find the page with minimum recent value (LRU)
    temp2 = lru_calculations[0];
    for (int j = 1; j < frames_count; j++) {
        if (temp2 > lru_calculations[j]) {
            temp2 = lru_calculations[j];
        }
    }

    // Find the victim page index
    for (int i = 0; i < frames_count; i++) {
        if (ref[temp2] == frames[i]) {
            return i;
        }
    }
    return 0;
}
