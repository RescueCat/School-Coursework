#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

struct cmd
  {
    int redirect_in;     /* Any stdin redirection?         */
    int redirect_out;    /* Any stdout redirection?        */
    int redirect_append; /* Append stdout redirection?     */
    int background;      /* Put process in background?     */
    int piping;          /* Pipe prog1 into prog2?         */
    char *infile;        /* Name of stdin redirect file    */
    char *outfile;       /* Name of stdout redirect file   */
    char *argv1[10];     /* First program to execute       */
    char *argv2[10];     /* Second program in pipe         */
  };

#define TRUE 1
#define FALSE 0

int 
cmdscan(char *cmdbuf, struct cmd *com)
{
  char *token;
  char *curcmd;        /* pointer to current command string */
  char swtch[256];    /* buffer to hold copy of switch */
  char *separators = " \t\n";
  int i;

  com->redirect_in = FALSE;
  com->redirect_out = FALSE;
  com->redirect_append = FALSE;
  com->background = FALSE;
  com->piping = FALSE;

  if ( (com->argv1[0] = strtok(cmdbuf,separators) ) == NULL)
    return(-1);
  i = 1;
  while( (com->argv1[i++] = (token = strtok(NULL,separators))) != NULL && strcmp(token,">") &&
        strcmp(token,"<") && strcmp(token,">>") && strcmp(token,"&") && strcmp(token,"|") );
  com->argv1[i-1] = NULL;

  if ( token != NULL && strcmp(token,"|") == 0 )
    {
      com->piping = TRUE;
      i = 0;
      while( (com->argv2[i++] = (token = strtok(NULL,separators))) != NULL && strcmp(token,">") &&
        strcmp(token,"<") && strcmp(token,">>") && strcmp(token,"&") && strcmp(token,"|") );
      com->argv2[i-1] = NULL;
      if ( com->argv2[0] == NULL )
        return(-1);
    }

  while ( token != NULL ){

    if ( !strcmp(token,">") || !strcmp(token,">>") )
      {
        if ( com->redirect_out )
          return(-1);
        com->redirect_out = TRUE;
        if ( !strcmp(token,">>") )
          com->redirect_append = TRUE;
        if ( (com->outfile = strtok(NULL,separators)) == NULL )
          return(-1);
      } 
    else if ( !strcmp(token,"<") )
      {
        if ( com->redirect_in )
          return(-1);
        com->redirect_in = TRUE;
        if ( (com->infile = strtok(NULL,separators)) == NULL )
          return(-1);
      } 
    else if ( !strcmp(token,"|") )
      {
        if ( com->piping )
          return(-1);
      } 
    else if ( !strcmp(token,"&") )
      {
        if ( com->background )
          return(-1);
        com->background = TRUE;
        if ( (token = strtok(NULL,separators)) != NULL )
          return(-1);
        break;
      }
    else
      return(-1);

    token = strtok(NULL,separators);
  }

  return(0);
}
