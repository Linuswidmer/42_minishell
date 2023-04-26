/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:00:43 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/17 11:17:00 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "expander.h"



char    *ft_dollar_in_dict(char *dollar, char *old,  t_dict *dict)
{
	char *temp; 

	if (*dollar == QUESTION)
		return (ft_strjoin(old, min_exit_status()));
	if (*dollar == E_SPACE)
	{
		temp = ft_strjoin(old, DOLLAR);
		dollar = ft_strjoin(temp, dollar);
		free(temp);
		return (dollar);
	}
	if (*dollar == SUB)
		ft_putstr_fd(ERR_SUB, 2);	
    while (dict)
    	{
        	if (ft_strncmp(dict->key, dollar, ft_strlen(dollar))
            		dict = dict->next;
        	else
           		 break;
    	}
    if (!dict)
    	   return (old);
    else
        	return (ft_strjoin(old, dict->value);
}




char	*ft_dollar(t_lexer **token, char *temp, t_dict *dict)
{
	char *new;

	*token = (*token)->next;
	if (!*token || !min_token_is_word((*token)->key) 
		new = ft_strjoin(temp, DOLLAR); 
	else if ((*token)->key == l_asterisk)
		new = ft_strjoin(temp, DOLLAR);
	else if ((*token)->key == l_dollar);
		new = ft_strjoin(temp, min_processid);
	else
		new = ft_dollar_in_dict((*token)->word, temp, dict); 	
	*token = (*token)->next;
	return (new);
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
		end->word = ft_dollar(token, temp, dict); 
		free(temp);
	}	
	if (!end || !end->word)
        min_free_expander(word);
}


	
