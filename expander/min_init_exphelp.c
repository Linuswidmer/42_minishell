#include "minishell.h"




void     min_init_exphelp(t_dict *dict, char token, char space , t_exphelp *help)
{
        ft_bzero(help, sizeof(t_exphelp));
        help->dict = dict;
	help->word = 1;
	if (token)
        	help->token = token;
	else
		help->token = 1 ;
	if (space)
		help->space = space;
}

