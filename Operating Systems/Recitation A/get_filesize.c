#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

void get_filesize(char *path) {
   struct stat statbuf;

   if (stat(path, &statbuf) == -1)
      perror("Failed to get file status");
   else
      printf("%s size is %d", path, size(&statbuf.st_size));
}
