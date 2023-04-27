/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:34:03 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/14 15:58:38 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	min_word(t_lexer **token, t_expander **word)
{
    t_expander  *end;
	char *temp;

    if ((*word)->key == l_empty)
	{
        (*word)->key = l_word;
		end = *word;
	}
    else
    {
        end = min_last_expander(*word);
		if (end->key == l_asterisk)
		{
        	end->next = min_init_expander(l_word);
        	end = end->next;
		}			
    }
	if (end)
	{
		temp = end->word;		
		end->word = ft_strjoin(temp, (*token)-value);
		free(temp);
	}	
	if (!end || !end->word)
		min_free_expander(word);
    *token = (*token)->next;
}


