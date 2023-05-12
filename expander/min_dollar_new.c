/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_dollar_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:00:18 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/12 16:22:26 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int ft_add_to_back(t_expander *word, char *value, char space)
{
	t_expander  *end;
	
	char *temp;

	
	
	if (word->key == l_empty space)
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
        		temp = end->word;
        		end->word = ft_strjoin( temp, (*token)->value);
        		min_free(&temp);
				
	
    }
    if (!end->word)
        min_free_expander(&word);		



			

	return (0);
}

char		min_dollar_new(t_lexer **token, t_expander **word, t_expander **extra, t_dict *dict, char space)
{
	(*token) = (*token)->next
	if (!*token || !min_token_is_word((*token)->key)
		return (min_word(NULL, word, DOLLAR, space)
	if (extra)
		ft_dollar_asterisk_mode(token, word, extra,  
	
