/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_word_eval.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:38:59 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/12 16:22:38 by jstrotbe         ###   ########.fr       */
/*   Updated: 2023/05/11 11:40:55 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	
static int	ft_count_values(t_expander *word)
{
	int c;

	c = 1;
	while (word)
	{
		if (word->key == l_space)
			c++;
		word = word->next;
	} 
	return (c);		
}


static char **ft_get_values(t_expander **word)
{
	char	**values;
	char	*temp;
	int		count;
	int		n;

	n = 0;
	if (!word)
		return (NULL);
	count = ft_count_values(*word);
	temp = NULL;
	values = ft_calloc(sizeof(char **) , (count +1));
	if (!values)
	{
		return (NULL);
	}
	while (*word)
	{	 
		if ((*word)->key == l_word)
		{
			if (!values[n])
			{	
				values[n] = ft_strdup((*word)->word); 
			}	
			else
			{
				temp = values[n];
				values[n] = ft_strjoin(temp, (*word)->word);
				//min_free(&temp);		
			}
		}
		else
			values[++n] = ft_strdup((*word)->word);
		if (!values[n])
		{
			//min_double_free(&values);
			*word = NULL;			
		}
		else					
			*word = (*word)->next;
	}
	if (values)
		values[n + 1] = NULL;
	return (values);
}


/* help struct for less varibels -> space && dict together*/
typdef struct s_exphelp t_exphelp;

struct s_exphelp{
	t_dict	*dict;
	char	space;
	char	export;
	char	token;
	char	word;
}		

static void	ft_init_exphelp(t_dict *dict, t_exphelp *help)
{
	ft_bezero(help, sizeof(t_exphelp));
	help->dict = dict;
	help->token = 1;
	help->word = 1;
}		

/* */
char **min_word_eval(t_lexer **token, t_dict *dict)
{
	char	**values;
	t_expander	*word;
	t_exphelp	help;
	
	ft_init_exphelp(dict, &help);
	word = min_init_expander(l_empty, EMPTY);
	while (word && *token && min_token_is_word((*token)->key))
	{
		if (min_token_is_word((*token)->key) == 1)
			min_word(token, word, NULL, help.space);
		else if (min_token_is_word((*token)->key) == 2)
			help.space = min_dollar(token, &word, help);
		else if ( min_token_is_word((*token)->key) == 4)
			help.space = min_til(token, &word, help);
		else 
			help.space = min_asterisk_new(token, &word, help);
	}

	values = ft_get_values(&word);	 
	min_free_expander(&word);
	return (values);
}
