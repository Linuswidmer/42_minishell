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
    t_expander  *end;
	char *temp;

    if (word->key == l_empty)
	{
        word->key = l_word;
		end = word;
	}
    else
    {
        end = min_last_expander(word);
    }
	if (end)
	{
		if (!space)
		{
			temp = end->word;
			end->word = ft_strjoin( temp, (*token)->value);
			min_free(&temp);
			if (!end->word)
        		min_free_expander(&word);
		}
		else
			min_addlast_expander(word, value, NULL)
	}
	if (token)
    	*token = (*token)->next;
	return (0);
}


