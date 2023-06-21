/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_til.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:40:07 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/05 11:38:36 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static  char    *ft_til_in_dict(t_dict *dict)
{
    char *temp;

    while (dict)
        {
            if (ft_strncmp(dict->key, HOME, ft_strlen(HOME)))
                    dict = dict->next_entry;
            else
                 break;
        }
    if (!dict)
           return (NULL);
    else
            return (dict->value);
}



void	min_til(t_lexer **token, t_expander **word, t_dict *dict)
{
	t_expander  *end;
    char *temp;
	char *value;
		
	if ((!(*token)->prev || !min_token_is_word((*token)->prev->key)) && ( !(*token)->next || !min_token_is_word((*token)->next->key)))
	{	
		value = ft_strdup(ft_til_in_dict(dict));
		if (!value)
			value = ft_strdup(EMPTY);
	}	
	else
		value = ft_strdup(TIL);
		
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
		if (temp) 
        	end->word = ft_strjoin(temp, value);
 		else
			end ->word = ft_strdup(value);
		//min_free(temp);
		//min_free(value);
    }
    if (!end || !end->word)
        min_free_expander(word);
    *token = (*token)->next;
}

