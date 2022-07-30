/*
 * Author : Cagatay KARASU
 * Since  : 09.05.2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// function to get Galton Board cells
int galtonBoard() {
  int sum = 0;
  for (int i = 0; i < 19; i++) {
    sum += rand() % 2;
  }
  return sum;
}

void * cell();

// declare array of Galton Board cells
int array[20];

// mutex for every cell
pthread_mutex_t mutex_array[20];

// function to prints Galton Board cells
void printGaltonBoardCells() {
  printf("Cell: Value\n-----------\n");
  for (int i = 0; i < 20; i++) {
      if (i < 10) printf("   %i: %i\n", i, array[i]);
      else printf(" %i: %i\n", i, array[i]);
  }
}

// function to get sum of Galton Board cells
int sumOfGaltonBoardCells() {
  int sum = 0;
  for (int i = 0; i < 20; i++) {
      sum += array[i];
  }
  return sum;
}

int main() {
  for (int i = 0; i < 20; i++) {
    pthread_mutex_init(&mutex_array[i], NULL);
  }

    // declare number of threads
int threadSize = 1000000;
pthread_t tids[threadSize];
pthread_attr_t attr;
pthread_attr_init(&attr);
int decision;
int success = 0;
srand(time(0));

for (int i = 0; i < threadSize; i++) {
  decision = pthread_create(&tids[i], &attr, &cell, NULL);
  if (decision == 0) {
    success++;
  }
}

for (int j = 0; j < success; j++) {
  pthread_join(tids[j], NULL);
}

printGaltonBoardCells();
printf("Successfully created threads: %i\n", success);
printf("Sum of values in the cell: %i\n\n\n", sumOfGaltonBoardCells());

return 0;
}

// declare cell
void * cell() {
    int index = galtonBoard();
    while (pthread_mutex_trylock(&mutex_array[index]) != 0);
    array[index]++;
    pthread_mutex_unlock(&mutex_array[index]);
}