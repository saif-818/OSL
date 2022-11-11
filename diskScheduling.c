#include <stdio.h>

#include <stdlib.h>

void FCFS() { 
int n, i, head;
printf("\nFCFS:\nEnter the size of request array:\t");
scanf("%d", & n);

int arr[n];
printf("Enter the elements of the requested array:\t");
for (i = 0; i < n; i++) scanf("%d", & arr[i]);

printf("Enter the current position of disk head:\t");
scanf("%d", & head);

int seek_count = 0;
int current_track;
for (int i = 0; i < n; i++) {
  current_track = arr[i];
  seek_count += abs(current_track - head);
  head = current_track;
}
printf("\nTotal number of seek operations is:\t%d", seek_count);
printf("\nSeek Sequence: ");
for (i = 0; i < n; i++) printf("%d ", arr[i]);
}

// Shortest Seek Time First 
void difference(int req_arr[], int diff[], int head, int n) {
  for (int i = 0; i < n; i++) diff[i] = abs(head - req_arr[i]);
}
int min_diff(int req_arr[], int visited[], int diff[], int head, int n) {
  int index = 0;
  int min = 9999;
  for (int i = 0; i < n; i++) {
    if (visited[i] == 0 && diff[i] < min) {`
      min = diff[i];
      index = i;
    }
  }
  return index;
}
void SSTF() {
  int n, i, head, index;
  printf("\nShortest Seek Time First:\nEnter the size of request array:\t");
  scanf("%d", & n);

  int arr[n];
  printf("Enter the elements of the requested array:\t");
  for (i = 0; i < n; i++) scanf("%d", & arr[i]);

  printf("Enter the current position of disk head:\t");
  scanf("%d", & head);

  int visited[100], diff[100];
  for (i = 0; i < n; i++) visited[i] = 0;

  int seek_count = 0;
  int seek_seq[n + 1];
  for (i = 0; i < n; i++) {
    seek_seq[i] = head;
    difference(arr, diff, head, n);
    index = min_diff(arr, visited, diff, head, n);
    visited[index] = 1;
    seek_count += diff[index];
    head = arr[index];
  }
  seek_seq[n] = head;
  printf("\n\nTotal Number of Seek Operations:\t%d", seek_count);
  printf("\nSeek Sequence is:\t");
  for (i = 0; i < n; i++) printf("%d ", seek_seq[i]);
}
// Scan 
void sort(int arr[], int size) {
  int swapped = 0;
  int temp;
  do {
    swapped = 0;
    for (int i = 0; i < size - 1; i++) {
      if (arr[i] > arr[i + 1]) {
        temp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = temp;
        swapped = 1;
      }
    }
  } while (swapped == 1);
}
void SCAN() {
  int n, i, head, disk_size, direction;
  printf("\nScan:\nEnter the size of request array:\t");
  scanf("%d", & n);
  printf("Enter the disk size:\t");
  scanf("%d", & disk_size);

  int arr[n];
  printf("Enter the elements of the requested array:\t");
  for (i = 0; i < n; i++) scanf("%d", & arr[i]);

  printf("Enter the current position of disk head:\t");
  scanf("%d", & head);
  printf("\nChoose a direction:\n 1 for Left\n 2 for Right\nOption Selected: ");
  scanf("%d", & direction);

  int seek_count = 0;
  int seek_seq[n];
  int l = 0, r = 0, seq = 0;
  int current_track;
  int left[100], right[100];

  if (direction == 2) right[r++] = disk_size - 1;
  else if (direction == 1) left[l++] = 0;

  for (i = 0; i < n; i++) {
    if (arr[i] < head) left[l++] = arr[i];
    if (arr[i] > head) right[r++] = arr[i];
  }
  sort(left, l);
  sort(right, r);

  int loop = 2;
  while (loop > 0) {
    if (direction == 2) {
      for (i = 0; i < r; i++) {
        current_track = right[i];
        seek_seq[seq++] = current_track;
        seek_count += abs(current_track - head);
        head = current_track;
      }
      direction = 1;
    } else if (direction == 1) {
      for (i = l - 1; i >= 0; i--) {
        current_track = left[i];
        seek_seq[seq++] = current_track;
        seek_count += abs(current_track - head);
        head = current_track;
      }
      direction = 2;
    }
    loop--;
  }
  printf("\n\nTotal Number of Seek Operations:\t%d", seek_count);
  printf("\nSeek Sequence is:\t");
  for (i = 0; i < n; i++) printf("%d ", seek_seq[i]);
}
void CLOOK() {
  int n, i, head;
  printf("\nC-Look:\nEnter the size of request array:\t");
  scanf("%d", & n);

  int arr[n];
  printf("Enter the elements of the requested array:\t");
  for (i = 0; i < n; i++) scanf("%d", & arr[i]);

  printf("Enter the current position of disk head:\t");
  scanf("%d", & head);

  int seek_count = 0;
  int seek_seq[n];
  int l = 0, r = 0, seq = 0;
  int current_track;
  int left[100], right[100];

  for (i = 0; i < n; i++) {
    if (arr[i] < head) left[l++] = arr[i];
    if (arr[i] > head) right[r++] = arr[i];
  }
  sort(left, l);
  sort(right, r);

  for (i = 0; i < r; i++) {
    current_track = right[i];
    seek_seq[seq++] = current_track;
    seek_count += abs(current_track - head);
    head = current_track;
  }
  seek_count += abs(head - left[0]);
  head = left[0];
  for (i = 0; i < l; i++) {
    current_track = left[i];
    seek_seq[seq++] = current_track;
    seek_count += abs(current_track - head);
    head = current_track;
  }
  printf("\n\nTotal Number of Seek Operations:\t%d", seek_count);
  printf("\nSeek Sequence is:\t");
  for (i = 0; i < n; i++) printf("%d ", seek_seq[i]);
}

int main() {
    int choice = 0;
    do {
      printf("\n\n---------------Disk Scheduling Algrotihms--------------- \n "); 
        printf("Press 1 for FCFS\nPress 2 for SSTF\nPress 3 for SCAN\nPress 4 for C-LOOK\nPress 5 to Exit\nChoice:\t"); scanf("%d", & choice);
        switch (choice) {
        case 1:
          FCFS();
          break;
        case 2:
          SSTF();
          break;
        case 3:
          SCAN();
          break;
        case 4:
          CLOOK();
          break;
        case 5:
          printf("\n\n-----------------------THANK YOU------------------------ \n \n ");             
          exit(0);         
          default:             
          printf("\n\n Enter options between 1 - 5. ");  
          break; 
          }

        }
        while (choice != 5);
        return 0;
      }