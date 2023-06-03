/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:34:03 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/11 11:04:52 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	min_word(t_lexer **token, t_expander *word)
{
    t_expander  *end;
	char *temp;

    if (word->key == l_empty)
	{
        word->key = l_word;
		end = word;
	}
    else
        end = min_last_expander(word);
	if (end)
	{	
		temp = end->word;
		end->word = ft_strjoin( temp, (*token)->value);
		min_free(&temp);
	}
	if (!end->word)
		min_free_expander(&word);	
    *token = (*token)->next;
}


