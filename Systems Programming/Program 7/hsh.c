#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

struct cmd 
{
  int redirect_in;
  int redirect_out;
  int redirect_append;
  int background;
  int piping;
  char *infile;
  char *outfile;
  char *argv1[10];
  char *argv2[10];
};

int cmdscan(char *cmdbuf, struct cmd *com);

int main() 
{
	struct cmd command;
    	char buf[1024];
    	int p, fd[2], fdin, fdout;
    
	while( fgets(buf, 1024, stdin) != NULL && strcmp(buf, "exit\n") != 0) 
	{
        	pipe(fd);
        	
		if( cmdscan( buf, &command ) ) 
		{
            		printf("Improper Format\n");
            		continue;
        	}
        	
		if( command.redirect_out == 1 ) 
		{
            		if( command.redirect_append == 1 )
                		fdout=open(command.outfile, O_CREAT | O_WRONLY | O_APPEND, 0600);
            		else
               			fdout=open(command.outfile, O_CREAT | O_WRONLY| O_TRUNC, 0600);
            		if( fdout < 0 ) 
			{
                		perror("fdout\n");
                		exit(0);
            		}
      		}
        	
		if ( command.redirect_in == 1 ) 
		{
            		if( (fdin=open(command.infile, O_RDONLY)) < 0 ) 
			{
                		perror("Infile Open ERROR");
                		exit(0);
            		}
       		}
        	
		switch ( fork() ) 
		{
            		case -1:
                		perror("fork error");
                		exit(0);
            		case 0:
            			if (command.background == 1) 
				{
                    			if(fork()>0) exit(0);
                    			sleep(2);
               			}
               	
				if(command.redirect_in == 1)
                    			dup2(fdin, STDIN_FILENO);
                
				if(command.piping == 1) 
				{
                   			close(fd[0]);
                   			dup2(fd[1], STDOUT_FILENO);
                   			close(fd[1]);
               			}
                	
				else if( command.redirect_out == 1 )
                    			dup2(fdout, STDOUT_FILENO);
                		
				execvp(command.argv1[0], command.argv1);
            		default:
            			if(command.piping == 1) 
				{
                    			switch( fork() ) 
					{
                        			case -1:
                            				perror("fork error");
                            				exit(0);
                       				case 0:
                            
                            				if (command.background == 1) 
							{
                                				if(fork()>0) exit(0);
                               					sleep(2);
                            				}
                            				close(fd[1]);
                            				dup2(fd[0], STDIN_FILENO);
                            				close(fd[0]);
                            		
							if ( command.redirect_out == 1 )
                            					dup2(fdout, STDOUT_FILENO);
                           	
							execvp(command.argv2[0], command.argv2);
                    			}
                		}
                		close(fd[0]);
                		close(fd[1]);
                		wait(NULL);
        	}
	}
    	
	return 0;
}
