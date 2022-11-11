#include<stdio.h>
#include<stdlib.h>

/* Function to take input for 2D array */
void takeInput(int * a, int p, int r) {
  for (int i = 0; i < p; i++) {
    for (int j = 0; j < r; j++) {
      scanf("%d", & a[i * r + j]);
    }
  }
}

/*Function to display output of 2D array for debugging 
void displayOutput(int *a,int p ,int r)
{
  for(int i=0;i<p;i++)
  {
    for(int j=0;j<r;j++)
    {
      printf(" %d ",a[i*r + j]);
    }
    printf("\n");   }
}
*/
/* Safety function to check if the state of the system after request is safe or unsafe */
int safety(int * need, int * allocation, int work[], int finish[], int r, int p) {

  int safeseq[p];
  int count = 0;

  while (count < p) {
    int status = 0;
    for (int i = 0; i < p; i++) {
      if (finish[i] == 0) {

        int j = 0;
        for (j = 0; j < r; j++) {
          if (need[i * r + j] > work[j])
            break;
        }

        if (j == r) {
          for (int k = 0; k < r; k++) {

            work[k] += allocation[i * r + k];

          }
          finish[i] = 1;
          safeseq[count++] = i;

          status = 1;

        }
      }

    }
    /* State is unsafe */
    if (status == 0) {
      return 0;
    }

  }

  /* State is safe and printing the safe sequence */
  printf("\nSAFE SEQUENCE");

  for (int i = 0; i < p; i++) {
    if (i == (p - 1))
      printf(" %d ", safeseq[i]);
    else
      printf(" %d --> ", safeseq[i]);

  }
  return 1;

}

/* Bankers function */
void
bankers(int * allocation, int available[], int * need, int r, int p) {

  int work[r];
  int finish[p];

  /* Initially setting finish for all process as false */
  for (int i = 0; i < p; i++) {
    finish[i] = 0;

  }
  printf("\nEnter the process number who requested resource :");
  int n = 3;
  scanf("%d", & n);
  int request[r];

  printf("Enter the request :");
  for (int i = 0; i < r; i++) {

    int a;

    scanf("%d", & a);
    request[i] = a;
  }
  // Check if the request <= need
  for (int i = 0; i < r; i++) {

    if (request[i] > need[n * r + i])
      return;
  }

  // Check if the request <= available 
  for (int i = 0; i < r; i++) {
    if (request[i] > available[i])
      return;
  }

  /* Assuming that the request was granted */
  for (int i = 0; i < r; i++) {
    available[i] = available[i] - request[i];

    allocation[n * r + i] = allocation[n * r + i] + request[i];
    need[n * r + i] = need[n * r + i] - request[i];

  }
  for (int i = 0; i < r; i++) {
    work[i] = available[i];
  }
  /* Now checking if the state is safe or unsafe after request is granted */
  int res = safety((int * ) need, (int * ) allocation, work, finish, r, p);

  if (res) {

    printf("\nThe request of process %d for resource is safe\n", n);

  } else {

    printf("\nThe request of process %d for resource is not safe\n", n);

  }

  return;

}

/*Main function */
int
main() {

  int r;

  printf("\nEnter total no of resources :");

  scanf("%d", & r);

  int p;

  printf("Enter total no of processes :");
  scanf("%d", & p);

  int allocation[p][r];
  int max[p][r];
  int need[p][r];
  int available[r];

  printf("\nEnter allocated resources for each process\n");
  takeInput((int * ) allocation, p, r);

  printf("\nEnter max resources needed for each process\n");
  takeInput((int * ) max, p, r); /* Calculating need matrix */

  for (int i = 0; i < p; i++) {
    for (int j = 0; j < r; j++) {
      int a = max[i][j];
      int b = allocation[i][j];
      need[i][j] = (a - b);

    }
  }
  printf("\nEnter available resources\n");

  for (int i = 0; i < r; i++) {
    int a;

    scanf("%d", & a);
    available[i] = a;

  }
  bankers((int * ) allocation, available, (int * ) need, r, p);
  return 0;

}