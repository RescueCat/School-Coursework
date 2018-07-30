#include <stdio.h>
#include <string.h>
#define MAX_INDEX 10
#define MAX_SIZE 6*MAX_INDEX

void fcfsa(char *s1, char *s2, int x1, int y1, int z1,
                        int x2, int y2, int z2);

static void runfcfsa(FILE *file, char *s1, char *s2,
               int i1, int i2, int i3, int i4, int i5, int i6) {
   memset(s1,'a',MAX_SIZE);
   memset(s2,'b',MAX_SIZE);
   fcfsa(s1,s2,i1,i2,i3,i4,i5,i6);
   fprintf(file,"%s\n",s1);
   fprintf(file,"%s\n",s2);
}
    
int main() {
   char s1[MAX_SIZE];
   char s2[MAX_SIZE];
   int i1,i2,i3,i4,i5,i6;
   FILE *f_fcfsa;
   f_fcfsa = fopen("fcfsa.all","w");
   if (f_fcfsa == NULL) {
      fprintf(stderr,"Error creating fcfsa.all\n");
      return 1;
   }
   fprintf(f_fcfsa,"FCFS Fall 2017\n");
   for (i1 = 1; i1 <= MAX_INDEX; i1++)
      for (i2 = 1; i2 <= MAX_INDEX; i2++)
         for (i3 = 1; i3 <= MAX_INDEX; i3++)
            for (i4 = 1; i4 <= MAX_INDEX; i4++)
               for (i5 = 1; i5 <= MAX_INDEX; i5++)
                  for (i6 = 1; i6 <= MAX_INDEX; i6++) {
                     runfcfsa(f_fcfsa,s1,s2,i1,i2,i3,i4,i5,i6);
                  }
   if (fclose(f_fcfsa) != 0)
       fprintf(stderr,"Error closing fcfsa.all\n");
   return 0;
}
