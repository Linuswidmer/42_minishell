#include "minishell.h"
void	min_dfree(char ***tofree)
{
	int i;
	
	i = 0;
	if (*tofree)
	{
		while ((*tofree)[i])
		{
			min_free(&((*tofree)[i]));
			i++;
		}
		free(*tofree);
		*tofree = NULL;
	}
}
