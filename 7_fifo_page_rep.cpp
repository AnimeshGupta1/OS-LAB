#include <stdio.h>

int main() {
  const int MAX_FRAMES = 50;
  int frames[MAX_FRAMES];
  int reference[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
  int num_frames = 3;
  int num_references = sizeof(reference) / sizeof(reference[0]);
  int num_page_faults = 0;
  int frame_index = 0;

  printf("FIFO Page Replacement Algorithm\n\n");

  printf("Reference String\tPage Frames\n");

  for (int i = 0; i < num_references; i++) {
    int page_found = 0;
    int page = reference[i];

    for (int j = 0; j < num_frames; j++) {
      if (frames[j] == page) {
        page_found = 1;
        break;
      }
    }

    if (!page_found) {
      frames[frame_index] = page;
      frame_index = (frame_index + 1) % num_frames;
      num_page_faults++;
    }

    printf("%4d\t\t", page);
    for (int j = 0; j < num_frames; j++) {
      printf("%4d", frames[j]);
    }
    printf("\n");
  }

  printf("\nTotal number of page faults: %d\n", num_page_faults);

  return 0;
}
