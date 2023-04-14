/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:00:43 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/14 15:58:27 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "expander.h"



char    *ft_dollar_in_dict(char *dollar, t_dict *dict)
{
        
    while (dict)
    {
        if (ft_strncmp(dict->key, dollar, ft_strlen(dollar))
            dict = dict->next;
        else
            break;
    }
    if (!dict)
    {
        if (ft_strncmp(dollar, DICT, ft_strlen(dollar)
            return (ft_strdup(DOLLAR));
        else
            return (ft_strdup());
    }   
    else
        return (ft_strdup((const char *)dict->value);
}




char	*ft_dollar(t_lexer **token, t_dict *dict)
{
	char *new;
	
	
	


}
void	min_dollar(t_lexer **token, t_expander **word, t_dict *dict)
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
		end->word = ft_dollar(token, dict); 
		free(temp);
	}	
	if (!end || !end->word)
        min_free_expander(word);
}


	
