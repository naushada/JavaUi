#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int rdFd[2];
	int wrFd[2];
	char *java_bin_name="First";
  int processPid = -1;
  char buff[512];
	int len = -1;

	if(pipe(rdFd))
  {
    fprintf(stderr, "\nOpening of Pipe (rdFd Failed\n");
    return(-1);		
	}			

  if(pipe(wrFd))
	{
    fprintf(stderr, "\nOpening of Pipe wrFd Failed\n");
    return(-2);		
	}	

  processPid = fork();
	if(!processPid)
	{
    /*Child Process*/					
    fprintf(stderr, "\nChild Process\n");
		close(rdFd[1]);
		close(wrFd[0]);

    while(1)
		{
			memset((void *)buff, 0, sizeof(buff));			
		  len = read(rdFd[0], buff, sizeof(buff));
		  if(len > 0)
		  {
		    fprintf(stderr,"\n Received from GUI %s \n", buff);
		    len = write(wrFd[1], buff, len);
		  }
			else
			{
			  perror("read Failed:");
				continue;
			}
		}
	}
  else
	{
	  /*Parent Process*/
	  close(rdFd[0]);
	  close(wrFd[1]);
		/*Mapping stdin to rdFd[1]*/
    if(dup2(rdFd[1], 1) < 0)
		{
		  perror("dup2: Failed to mapp stdin");
			return(-1);
		}

		/*Mapping stdout to wrFd[0[*/
    if(dup2(wrFd[0], 0) < 0)
		{
		  perror("dup2:Mapp to stdout failed");
			return(-1);
		}

	  if(execlp("/usr/bin/java", "/usr/bin/java",java_bin_name, NULL) < 0)
		{
		  fprintf(stderr, "\nExecution of Java Binary Failed\n");
      perror("Error:");
      close(rdFd[1]);
      close(wrFd[0]);			
		}
	}
}
