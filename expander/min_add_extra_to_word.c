#include "minishell.h"


void	min_add_extra_to_word(t_expander **word, t_expander *extra)
{
	if (!extra)
		return ;
	while (extra)
	{
		if (min_addlast_expander(word, extra->word, NULL))
			break ;
		extra = extra->next;
	}
}
