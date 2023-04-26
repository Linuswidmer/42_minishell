  #include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main (void)
{
  char *pwd;

  pwd = getcwd(NULL, 0);
  if (pwd)
  {
    printf("%s\n", pwd);
	free(pwd);
    return (0);
  }
  else
		return (1);
 } 	
