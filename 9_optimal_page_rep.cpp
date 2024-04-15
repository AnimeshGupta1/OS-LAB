#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 50
#define MAX_REFERENCE_STR 50

int num_frames, num_references, page_faults = 0;
int reference[MAX_REFERENCE_STR], frames[MAX_FRAMES], opt_calculations[MAX_FRAMES], recent[10], count = 0;

// Function to find the victim page using the Optimal algorithm
int get_optimal_victim(int index);

int main() {
    printf("\nOPTIMAL PAGE REPLACEMENT ALGORITHM\n");

    // Input number of frames and reference string
    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);
    printf("Enter the size of reference string: ");
    scanf("%d", &num_references);
    printf("Enter the reference string (separated by space): ");
    for (int i = 0; i < num_references; i++)
        scanf("%d", &reference[i]);

    printf("\nOPTIMAL PAGE REPLACEMENT ALGORITHM\n");
    printf("\nReference String\tPage Frames\n");

    // Initialize arrays
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        opt_calculations[i] = 0;
    }

    for (int i = 0; i < 10; i++)
        recent[i] = 0;

    // Process the reference string
    for (int i = 0; i < num_references; i++) {
        int flag = 0;
        printf("\n%d\t\t\t\t", reference[i]);

        // Check if page already in frames
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == reference[i]) {
                flag = 1;
                break;
            }
        }

        // Page fault handling
        if (flag == 0) {
            page_faults++;

            // Find victim page using Optimal algorithm
            int victim = get_optimal_victim(i);
            frames[victim] = reference[i];

            // Display current page frames
            for (int j = 0; j < num_frames; j++)
                printf("%4d", frames[j]);
        }
    }

    // Print total number of page faults
    printf("\n\nNumber of page faults: %d\n", page_faults);
    return 0;
}

// Function to find the victim page using the Optimal algorithm
int get_optimal_victim(int index) {
    int not_found, temp;
    for (int i = 0; i < num_frames; i++) {
        not_found = 1;
        for (int j = index; j < num_references; j++) {
            if (frames[i] == reference[j]) {
                not_found = 0;
                opt_calculations[i] = j;
                break;
            }
        }
        if (not_found == 1)
            return i;
    }
    temp = opt_calculations[0];
    for (int i = 1; i < num_frames; i++) {
        if (temp < opt_calculations[i])
            temp = opt_calculations[i];
    }
    for (int i = 0; i < num_frames; i++)
        if (frames[temp] == frames[i])
            return i;
    return 0;
}
