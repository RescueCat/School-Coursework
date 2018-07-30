#include <stdio.h>
#include <string.h>
#define MAX_INDEX 10
#define MAX_SIZE 6*MAX_INDEX

void fcfs(char *s1, char *s2, int x1, int y1, int z1,
                        int x2, int y2, int z2);
void sjf(char *s1, char *s2, int x1, int y1, int z1,
                        int x2, int y2, int z2);
void psjf(char *s1, char *s2, int x1, int y1, int z1,
                        int x2, int y2, int z2);
void rr(char *s1, char *s2, int quantum, int x1, int y1, int z1,
                        int x2, int y2, int z2);

static void runfcfs(FILE *file, char *s1, char *s2,
               int i1, int i2, int i3, int i4, int i5, int i6) {
   memset(s1,'a',MAX_SIZE);
   memset(s2,'b',MAX_SIZE);
   fcfs(s1, s2, i1, i2,i3,i4,i5,i6);
   fprintf(file,"%s\n",s1);
   fprintf(file,"%s\n",s2);
}
    
static void runsjf(FILE *file, char *s1, char *s2,
               int i1, int i2, int i3, int i4, int i5, int i6) {
   memset(s1,'a',MAX_SIZE);
   memset(s2,'b',MAX_SIZE);
   sjf(s1, s2, i1, i2,i3,i4,i5,i6);
   fprintf(file,"%s\n",s1);
   fprintf(file,"%s\n",s2);
}

static void runpsjf(FILE *file, char *s1, char *s2,
               int i1, int i2, int i3, int i4, int i5, int i6) {
   memset(s1,'a',MAX_SIZE);
   memset(s2,'b',MAX_SIZE);
   psjf(s1, s2, i1, i2,i3,i4,i5,i6);
   fprintf(file,"%s\n",s1);
   fprintf(file,"%s\n",s2);
}


static void runrr(FILE *file, char *s1, char *s2, int q,
               int i1, int i2, int i3, int i4, int i5, int i6) {
   memset(s1,'a',MAX_SIZE);
   memset(s2,'b',MAX_SIZE);
   rr(s1, s2, q,i1, i2,i3,i4,i5,i6);
   fprintf(file,"%s\n",s1);
   fprintf(file,"%s\n",s2);
}

int main() { char s1[MAX_SIZE];
   char s2[MAX_SIZE];
   int i1,i2,i3,i4,i5,i6;
   FILE *f_fcfs;
   FILE *f_sjf;
   FILE *f_psjf;
   FILE *f_rr;
   f_fcfs = fopen("fcfs.all","w");
   if (f_fcfs == NULL) {
      fprintf(stderr,"Error creating fcfs.all\n");
      return 1;
   }
   fprintf(f_fcfs,"FCFS Fall 2017\n");
   f_sjf = fopen("sjf.all","w");
   if (f_sjf == NULL) {
      fprintf(stderr,"Error creating sjf.all\n");
      return 1;
   }
   fprintf(f_sjf,"SJF Fall 2017\n");
   f_psjf = fopen("psjf.all","w");
   if (f_psjf == NULL) {
      fprintf(stderr,"Error creating psjf.all\n");
      return 1;
   }
   fprintf(f_psjf,"PSJF Fall 2017\n");
   f_rr = fopen("rr.all","w");
   if (f_rr == NULL) {
      fprintf(stderr,"Error creating rr.all\n");
      return 1;
   }
   fprintf(f_rr,"RR Fall 2017\n");
   for (i1 = 1; i1 <= MAX_INDEX; i1++)
      for (i2 = 1; i2 <= MAX_INDEX; i2++)
         for (i3 = 1; i3 <= MAX_INDEX; i3++)
            for (i4 = 1; i4 <= MAX_INDEX; i4++)
               for (i5 = 1; i5 <= MAX_INDEX; i5++)
                  for (i6 = 1; i6 <= MAX_INDEX; i6++) {
                     runfcfs(f_fcfs,s1,s2,i1,i2,i3,i4,i5,i6);
                     runsjf(f_sjf,s1,s2,i1,i2,i3,i4,i5,i6);
                     runpsjf(f_psjf,s1,s2,i1,i2,i3,i4,i5,i6);
                     runrr(f_rr,s1,s2,3,i1,i2,i3,i4,i5,i6);
                  }
   if (fclose(f_fcfs) != 0)
       fprintf(stderr,"Error closing fcfs.all\n");
   if (fclose(f_sjf) != 0)
       fprintf(stderr,"Error closing sjf.all\n");
   if (fclose(f_psjf) != 0)
       fprintf(stderr,"Error closing psjf.all\n");
   if (fclose(f_rr) != 0)
       fprintf(stderr,"Error closing rr.all\n");
   return 0;
}
