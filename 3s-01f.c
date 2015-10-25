#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_THREADS 8
#define VECTOR_SIZE 1000000000

pthread_t tid[MAX_THREADS];

int *array;
float  arraytime[MAX_THREADS];
int length = VECTOR_SIZE;
int count = 0;
int double_count = 0;
int max_threads = MAX_THREADS;

void *count3s_thread(void *arg) {
  int i;
  clock_t   t1th, t2th;
  int length_per_thread = length/max_threads;
  // Cast -> http://stackoverflow.com/questions/1640423/error-cast-from-void-to-int-loses-precision
  int id = (int)arg;
  int start = id * length_per_thread;
  printf("\tThread [%d] starts [%d] length [%d]\n",id, start, length_per_thread);
  t1th=clock();
  for (i = start; i < start + length_per_thread; i++) {
    if (array[i] == 3) {
      count++;
    }
  }
  t2th=clock();
  arraytime[id]=(((float)t2th - (float)t1th) / 1000000.0F ) * 1000;
}


void initialize_vector() {
  int i = 0;
  array = (int*) malloc(sizeof(int) * VECTOR_SIZE);
  if (array == NULL) {
    printf("Allocation memory failed!\n");
    exit(-1);
  }
  for (; i < VECTOR_SIZE; i++) {
    array[i] = rand() % 20;
    if (array[i] == 3)
      double_count++;
  }
}

int main(int argc, char* argv[]) {
  int i = 0;
  int err;
  clock_t t1, t2, t1ini, t2ini,t1th, t2th;
  if (argc == 2) {
    max_threads = atoi(argv[1]);
    if (max_threads > MAX_THREADS)
      max_threads = MAX_THREADS;
  } else {
    max_threads = MAX_THREADS;
  }
  printf("[3s-01] Using %d threads\n",max_threads);
  // random seed
  // http://stackoverflow.com/questions/822323/how-to-generate-a-random-number-in-c
  srand(time(NULL));
  printf("*** 3s-01 ***\n");
  printf("Initializing vector... ");
  fflush(stdout);
  t1ini= clock();
  initialize_vector();
  t2ini= clock();
  printf("Vector initialized!\n");
  fflush(stdout);
  t1 = clock();
  while (i < max_threads) {
   
    err = pthread_create(&tid[i], NULL, &count3s_thread, (void*)i);
    if (err != 0) 
      printf("[3s-01] Can't create a thread: [%d]\n", i);
    else
      printf("[3s-01] Thread created!\n");
      i++;
  }
  t2 = clock();
  printf("[3s-01] Count by threads %d\n", count);
  printf("[3s-01] Double check %d\n", double_count);
  printf("[[3s-01] Initializing time %f\n", (((float)t2ini - (float)t1ini) / 1000000.0F ) * 1000);
  //printf("[[3s-01] Elapsed time %ld ms\n", (ti2 - t1) / CLOCKS_PER_SEC * 1000);
  printf("[[3s-01] Elapsed time %f\n", (((float)t2 - (float)t1) / 1000000.0F ) * 1000);
  for(i=0; i<MAX_THREADS; i++){
    printf("[[3s-01] Elapsed time thread [%d] = %f\n",i, arraytime[i]);
  }
  return 0;
}
