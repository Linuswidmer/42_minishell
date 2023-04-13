#include "builtins.h"
#include "libft.h"

int min_exit (char *arg)
{
  int status;

  if (arg)
    status = ft_atoi(arg);
  else
    status = 1;
  return (status);
}
