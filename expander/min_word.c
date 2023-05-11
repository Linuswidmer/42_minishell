/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:34:03 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/09 17:34:44 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        end->next = min_init_expander(l_word);
        end = end->next;			
    }
	if (end)
	{	
		end->word = ft_strdup((*token)->value);

	}
	if (!end || !end->word)
		min_free_expander(word);	
    *token = (*token)->next;
}


