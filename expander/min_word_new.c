/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:34:03 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/12 16:22:50 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




char	min_word(t_lexer **token, t_expander **word, char *value,  char space)
{
	t_expander  	*end;
	char		*temp;
	
	if (!*word)
		*word = min_init_expander(l_empty, EMPTY); 				
	if (*word && (*word)->key == l_empty)
	{
		(*word)->key = l_word;
		end = *word;
	}
    	else
    	{
        	end = min_last_expander(*word);
    	}
	if (end)
	{
		if (space)
		{
			end->next =  min_init_expander(l_word, EMPTY);
			if (!end->next)
			{
                                min_free_expander(word);
				return (0);
			}
			end = end->next;
		}
		temp = end->word;
		if (value)
			end->word = ft_strjoin( temp, value);
		else
			end->word = ft_strjoin( temp, (*token)->value);
		min_free(&temp);
		if (!end->word)
			min_free_expander(word);
		}
	}
	if (token)
    		*token = (*token)->next;
	return (0);
}


