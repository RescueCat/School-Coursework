#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void* sort(void *args);
void* merge(void *args);

struct sortparam_s {
    int beg;
    int end;
    double *arr;
};

struct mergeparam_s {
    int mid;
    int n;
    double *in; /* input array */
    double *out; /* merged array */
};


int main(int argc, char *argv[]) {
pthread_t t1;
pthread_t t2;
pthread_t t3;

struct sortparam_s p1, p2;
struct mergeparam_s p3;

int mid, N, i;

double * arr; /* array */
double * arr2; /* Used for a copy */
double * merged; /* For storing the merged array */

clock_t start, diff;

if(argc != 2) {
      printf("Usage: %s <N>\n", argv[0]);
      return -1;
}

N = atoi(argv[1]);
arr = (double*)malloc(N * sizeof(double));
arr2 = (double*)malloc(N * sizeof(double));
merged = (double*)malloc(N * sizeof(double));

srand(time(NULL));

/* printf ("Array: "); */
for(i = 0; i < N; i++) { /* generate random numbers */
    arr[i] = arr2[i] = (double)rand() / RAND_MAX * 99.0 + 1.0; /* range 1.0 - 100.0 */
    /* printf("%f ", arr[i]); */
}
/* printf("\n"); */

p1.beg = 0;
p1.end = N/2;
p1.arr = arr;

p2.beg = N/2;
p2.end = N;
p2.arr = arr;

p3.mid = N/2;
p3.n = N;
p3.in = arr;
p3.out = merged;

start = clock(); /* start time */

/* Start the threads for working on sub arrays */
pthread_create(&t1, NULL, sort, &p1);
pthread_create(&t2, NULL, sort, &p2);

/* Wait for sorting to complete */
pthread_join(t1, NULL);
pthread_join(t2, NULL);

/* Start thread for merge */
pthread_create(&t3, NULL, merge, &p3);
/* Wait for merge thread to complete */
pthread_join(t3, NULL);

diff = clock() - start; /* End time */

printf("Sorting is done in %fms when two threads are used\n", diff * 1000.0f / CLOCKS_PER_SEC);

p1.end = N; /* To run on the whole array */
p1.arr = arr2; /* arr is already partially sorted. Pass the copy of original array */

start = clock(); /* start time */

sort(&p1);

diff = clock() - start; /* End time */

printf("Sorting is done in %fms when one thread is used\n", diff * 1000.0f / CLOCKS_PER_SEC);

free(arr);
free(arr2);
free(merged);
return 0;
}

void* sort(void *args) {
int i, j, min;
double tmp;
double *arr;
struct sortparam_s* p = (struct sortparam_s*) args;
arr = p->arr;
/* printf("sort %d to %d: ", p->beg, p->end); */
for(i = p->beg; i < p->end; i++) {
    min = i;
    for(j = i + 1; j < p->end; j++) {
      if(arr[j] < arr[min])
        min = j;
    }
    tmp = arr[i];
    arr[i] = arr[min];
    arr[min] = tmp;
}
/*for(i = p->beg; i < p->end; i++)
      printf("%f ", arr[i]);
printf("\nEnd sort\n"); */
return NULL;
}

void* merge(void *args) {
int i,j,k;
double *in, *out;
struct mergeparam_s* p = (struct mergeparam_s*) args;
/* printf("Merge %d : ", p->n); */
i = k = 0;
j = p->mid;
in = p->in;
out = p->out;
while(i < p->mid && j < p->n) {
    if(in[i] < in[j])
      out[k++] = in[i++];
    else
      out[k++] = in[j++];
}
while(i < p->mid)
    out[k++] = in[i++];
while(j < p->n)
    out[k++] = in[j++];
/* for(i = 0; i < p->n; i++)
      printf("%f ", out[i]);
printf("\n"); */
return NULL;
}
