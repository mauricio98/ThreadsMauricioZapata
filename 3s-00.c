#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_THREADS 4
#define VECTOR_SIZE 1000000000

pthread_t tid[MAX_THREADS];

int *array;
int count = 0;
int double_count = 0;
int max_threads = 0;


void initialize_vector() {
  int i = 0;
  array = (int*) malloc(sizeof(int) * VECTOR_SIZE);
  if (array == NULL) {
    printf("Allocation memory failed!\n");
    exit(-1);
  }
  for (; i < VECTOR_SIZE; i++) {
    array[i] = rand() % 20;
  }
}
void Dcount() {
  int i=0;
  for (; i < VECTOR_SIZE; i++) {
    if (array[i] == 3)
      double_count++;
  }
}

void count_3s() {
  int i = 0;
  for (; i < VECTOR_SIZE; i++) {
    if (array[i] == 3) count++;
  }
}

int main(int argc, char* argv[]) {
  int i = 0;
  int err;
  clock_t t1, t2, t1ini, t2ini, t1Dcount, t2Dcount;
  
  if (argc == 2) {
    max_threads = atoi(argv[1]);
  } else {
    max_threads = MAX_THREADS;
  }
  printf("Running 3s-00");
  // random seed
  // http://stackoverflow.com/questions/822323/how-to-generate-a-random-number-in-c
  srand(time(NULL));
  printf("*** 3s-00 ***\n");
  printf("Initializing vector... ");
  fflush(stdout);
  t1ini= clock();
  initialize_vector();
  t2ini= clock();
  printf("Vector initialized!\n");
  fflush(stdout);
  t1 = clock();
  count_3s();
  t2 = clock();
  t1Dcount= clock();
  Dcount();
  t2Dcount= clock();
  
  printf("Count by threads %d\n", count);
  printf("Double check %d\n", double_count);
  printf("[[3s-00] Initializing time %f\n", (((float)t2ini - (float)t1ini) / 1000000.0F ) * 1000);
  printf("[[3s-00] Elapsed time count %f\n", (((float)t2 - (float)t1) / 1000000.0F ) * 1000);
  printf("[[3s-00] Elapsed time Double count %f\n", (((float)t2Dcount - (float)t1Dcount) / 1000000.0F ) * 1000);  
  printf("Finishing 3s-00");
  return 0;
}
