#include "builtins.h"

int pwd()
{
  char *pwd;

  pwd = getcwd(NULL, 0);
  if (pwd)
  {
    printf("%s\n", pwd);
    return (0);
  }
  else
    return (1);
}
