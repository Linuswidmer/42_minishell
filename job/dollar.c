/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 07:46:44 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/14 15:58:43 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"  



char 	*ft_dollar_in_dict(char *dollar, t_dict *dict)
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
			return (ft_strdup(DICT));
	}	
	else
		return (ft_strdup((const char *)dict->value);	
}
	
int	ft_len_word(char *input, char dollar)
{
	int len;

	len = 0;
	while (*input)
	{
		if (dollar && ((*input == "$" && len) || *input == " ")
			break;
		if (!dollar && *input == "$" ) 
			break;
		len++;
		input++;
	}	
	return (len)
}





void	ft_next_token(t_dollar **token, char dollar, char *input, int end)  
{
	t_dollar *end;

	if (!*token)
	{
		*token = ft_init_dollar(dollar);
		end = *token;
	}
	else
	{
		end = ft_last_token(*token);
		end->next = ft_init_dollar(dollar);
		end = end->next;
	}
	if (end)
	{
		if (dollar && *input == "(" 



	}
	else
		ft_free_token(token);
}	



t_dollar *ft_dollartoken(char *input)
{
	t_dollar	*token;
	int			end;
	
	token = NULL;
	while (input)
	{
		if (*input != "$")	
		{
			end = ft_len_word(input, 0);
			ft_next_token(&token, 0 , end);
		}	
		else
		{
			end =  ft_len_word(input++, 1);
			ft_next_token(&token, 1 , end);	
		}
		if (input)
			input++
		
	}





char	*min_dollar(char *token, t_dict *dict)
{
	t_dollar *dollar;
	char *value;
	char *temp;
	char *new,

	dollar = ft_dollartoken(token);
	

	value = (char *)malloc(sizeof(char));
	if (value)
		ft_bzero(value, sizeof(char));	
	while(dollar  && value)
	{	temp = value;
		if (dollar->key == l_word)
			new = ft_strdup(dollar->word);
		else if (!dollar->ast)
			new = ft_dollar_in_dict(dollar->word, dict);
		else
		{
			new = ft_dollar_in_dict(dollar->word, dict);
			/* print that this is not our task */
		}	 	
		value =  ft_strjoin(temp, new);
		free(temp)
		free(new);
		dollar = dollar->next;
	}
	return (value);
}	
