#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#define MILLION 1000000L

int increment();
int getcount(int *thecount);

static void *incthread(void *arg) {
   int num;
   int i;
   char c;
   num = *(int *)arg;
   fprintf(stderr,"incthread started: %d\n",num);
   for (i=0;i<num;i++)
      increment();
   fprintf(stderr,"incthread done\n");
   return NULL;
}

int main(int argc, char *argv[]) {
   pthread_t *tids;
   int final_count;
   int numthreads;
   int incsperthread;
   int i;

   if (argc != 3) {
      fprintf(stderr,"Usage: %s numthreads incsperthread\n",argv[0]);
      return 1;
   }
   numthreads = atoi(argv[1]);
   incsperthread = atoi(argv[2]);
   tids = (pthread_t *)malloc(numthreads*sizeof(pthread_t *));
   if (tids == NULL) {
      fprintf(stderr,"Error allocating space for %d thread ids\n",numthreads);
      return 1;
   }
   
   
   long timedif;
   struct timeval tpend;
   struct timeval tpstart;

   if (gettimeofday(&tpstart, NULL)) {
      fprintf(stderr, "Failed to get start time\n");
      return 1;
   }
   
   for (i=0;i<numthreads;i++)
     if (pthread_create(tids+i,NULL,incthread,&incsperthread)) {
        fprintf(stderr,"Error creating thread %d\n",i+1);
        return 1;
     }
   for (i=0;i<numthreads;i++)
     if (pthread_join(tids[i],NULL)) {
        fprintf(stderr,"Error joining thread %d\n",i+1);
        return 1;
     }
   
   if (gettimeofday(&tpend, NULL)) {
      fprintf(stderr, "Failed to get end time\n");
      return 1;
   }
   timedif = MILLION*(tpend.tv_sec - tpstart.tv_sec) +
                      tpend.tv_usec - tpstart.tv_usec;
   printf("The function_to_time took %ld microseconds\n", timedif);
   
   fprintf(stderr,"Count should be %d\n",numthreads*incsperthread);
   getcount(&final_count);
   fprintf(stderr,"Count is        %d\n",final_count);
   return 0;
}
   
