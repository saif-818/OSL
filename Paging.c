#include <stdio.h>

#include <stdlib.h>

int pages[20];
int frames[20];
int hit = 0, ishit;
int miss = 0;
int pageFaultCount = 0;
int noOfPages;
int noOfFrames;
void getData() {
  printf("Enter the length of page reference sequence: ");
  fflush(stdout);
  scanf("%d", & noOfPages);
  printf("Enter the page reference sequence: ");
  fflush(stdout);
  for (int i = 0; i < noOfPages; i++) scanf("%d", & pages[i]);
  printf("Enter the no of frames: ");
  fflush(stdout);
  scanf("%d", & noOfFrames);
}
void init() {
  hit = 0;
  miss = 0;
  for (int i = 0; i < noOfFrames; i++)
    frames[i] = 9999;
  pageFaultCount = 0;
}
int isHit(int page) {
  ishit = 0;
  for (int i = 0; i < noOfFrames; i++) {
    if (frames[i] == page) {
      ishit = 1;
      hit++;
      break;
    }
  }
  return ishit;
}
void displayPageFaultCount() {
  printf("Total no of page faults: %d\n", pageFaultCount);
  fflush(stdout);
}
void displayPages() {
  for (int i = 0; i < noOfFrames; i++) {
    if (frames[i] != 9999) {
      printf(" %d", frames[i]);
      fflush(stdout);
    }
  }
}
void fifo() {
  init();
  fflush(stdout);
  int k = 0;
  for (int i = 0; i < noOfPages; i++) {
    printf("\nFor %d: ", pages[i]);
    fflush(stdout);
    if (isHit(pages[i]) == 0) {
      printf("Miss!");
      fflush(stdout);
      for (k = 0; k < noOfFrames - 1; k++) frames[k] = frames[k + 1];
      frames[k] = pages[i];
      pageFaultCount++;
      displayPages();
    } else {
      printf("Hit!");
      fflush(stdout);
      displayPages();
    }
  }
  displayPageFaultCount();
}
void lru() {
  init();
  fflush(stdout);
  int least[20];
  int i, j, k;
  for (i = 0; i < noOfPages; i++) {
    printf("\nFor %d : ", pages[i]);
    fflush(stdout);
    if (isHit(pages[i]) == 0) {
      printf("Miss!");
      fflush(stdout);
      for (j = 0; j < noOfFrames; j++) {
        int pg = frames[j];
        int found = 0;
        for (k = i - 1; k >= 0; k--) {
          if (pg == pages[k]) {
            least[j] = k;
            found = 1;
            break;
          } else found = 0;
        }
        if (!found) least[j] = -9999;
      }
      int min = 9999;
      int leastindex;
      for (j = 0; j < noOfFrames; j++) {
        if (least[j] < min) {
          min = least[j];
          leastindex = j;
        }
      }
      frames[leastindex] = pages[i];
      pageFaultCount++;
      displayPages();
    } else {
      printf("Hit!");
      fflush(stdout);
      displayPages();
    }
  }
  displayPageFaultCount();
}
void optimal() {
  init();
  fflush(stdout);
  int opt[20];
  int i, j, k;
  for (i = 0; i < noOfPages; i++) {
    printf("\nFor %d : ", pages[i]);
    fflush(stdout);
    if (isHit(pages[i]) == 0) {
      printf("Miss!");
      fflush(stdout);
      for (j = 0; j < noOfFrames; j++) {
        int pg = frames[j];
        int found = 0;
        for (k = i; k < noOfPages; k++) {
          if (pg == pages[k]) {
            opt[j] = k;
            found = 1;
            break;
          } else found = 0;
        }
        if (!found) opt[j] = 9999;
      }
      int max = -9999;
      int mostindex;
      for (j = 0; j < noOfFrames; j++) {
        if (opt[j] > max) {
          max = opt[j];
          mostindex = j;
        }
      }
      frames[mostindex] = pages[i];
      pageFaultCount++;
      displayPages();
    } else {
      printf("Hit!");
      fflush(stdout);
      displayPages();
    }
  }
  displayPageFaultCount();
}
void menu() {
  printf("1. FIFO\n");
  printf("2. LRU\n");
  printf("3. Optimal\n");
  printf("4. Exit\n");
  printf("Enter your choice\n");
}
int main() {
  int ch;
  while (1) {
    menu();
    fflush(stdout);
    scanf("%d", & ch);
    switch (ch) {
    case 1:
      printf("\n***** FIFO *****\n");
      getData();
      fifo();
      break;
    case 2:
      printf("\n***** LRU *****\n");
      getData();
      lru();
      break;
    case 3:
      printf("\n***** Optimal *****\n");
      getData();
      optimal();
      break;
    case 4:
      fflush(stdout);
      return 0;
    default:
      break;
    }
  }
  return 0;
}