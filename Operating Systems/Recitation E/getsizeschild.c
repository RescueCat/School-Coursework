#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

static char *filename1;
static char *filename2;

static int size1 = 0;
static int size2 = 0;
static int total = 0;
static int status = 0;
static int total2 = 0;

static int get_filesize(char *path) {
   struct stat statbuf;

   if (stat(path, &statbuf) == -1)
      return -1;
   return (int)statbuf.st_size;
}

int main (int argc, char *argv[]) {
   int childpid;

   if (argc != 3) {
      fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
      return 1;
   }
   filename1 = argv[1];
   filename2 = argv[2];

   childpid = fork();
   if (childpid < 0) {
      fprintf(stderr,"Error creating child process\n");
      return 1;
   }
   if (childpid == 0) {                                     /* child code */
      size1 = get_filesize(filename1);
      fprintf(stderr,"Size of %s is %d\n", filename1, size1);
      total2 += size1;
      return 0;
   }
	wait();
   size2 = get_filesize(filename2);
   total += size2;
	total+= total2;
	//waitpid(childpid, &status,
   fprintf(stderr,"Size of %s is %d\n", filename2, size2);
   fprintf(stderr,"Total size is %d\n", total);
   return 0; 
}

