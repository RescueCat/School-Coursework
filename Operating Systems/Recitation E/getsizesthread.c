#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

static char *filename1;
static char *filename2;

static int size1 = 0;
static int size2 = 0;
static int total = 0;

static int get_filesize(char *path) {
   struct stat statbuf;

   if (stat(path, &statbuf) == -1)
      return -1;
   return (int)statbuf.st_size;
}

static void *sizethread(void *arg) {
   size1 = get_filesize(filename1);
   fprintf(stderr,"Size of %s is %d\n", filename1, size1);
   total+= size1;
   return NULL;
}

int main (int argc, char *argv[]) {
   int error;
   pthread_t tid;

   if (argc != 3) {
      fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
      return 1;
   }
   filename1 = argv[1];
   filename2 = argv[2];

   if (error = pthread_create(&tid, NULL, sizethread, NULL)) {
      fprintf(stderr, "Failed to create thread: %s\n", strerror(error));
      return 1;
   }
   if (error = pthread_join(tid, NULL)) {
      fprintf(stderr, "Failed to join thread: %s\n", strerror(error));
      return 1;
   }

   size2 = get_filesize(filename2);
   total += size2;
   fprintf(stderr,"Size of %s is %d\n", filename2, size2);
   fprintf(stderr,"Total size is %d\n", total);
   return 0; 
}

