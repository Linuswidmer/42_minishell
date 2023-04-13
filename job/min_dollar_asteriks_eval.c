/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_dollar_asteriks_eval.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:22:01 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/12 16:38:27 by jstrotbe         ###   ########.fr       */
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

t_dollar *ft_dollartoken(char *input)
{
	bool	 dollar;
	t_dollar *token;
	
	while (input)
	{
		if (*input != "$")	
		{
		len = ft_len_word(		
		ft_next_token(&token, 0 , substr(input, 0 , end));
		}	
		else
			ft_next_token(&token, 1 , substr(input, 0 , end));	
		if (input)
			input++
	}





char	*ft_dollar(char *token, t_dict *dict)
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




char	*ft_dollar_eval(t_lexer *token, t_dict *dict)
{
	if (token->key == l_word)
		return (ft_strdup((const char *)token->value);
	else	
		return (ft_dollar(token->value, dict);
}



 

void	ft_add_value_to_word(t_expander **word, t_lexer *token, t_dict *dict)
{
	t_expander *end;
	char *temp;
	char *value;
	
	if (!word)
		*word = ft_init_expander();	
	end = ft_last(*word);
	if (end && end->value == l_asterisk)
	{
		end->next = ft_init_expander();
		if (!end->next)
			ft_free_words(word);	 
		end = end->next;
	}
	if (end)
	{
		if (!end->word)
			end->word = ft_dollar_eval(token, dict);		
		else
		{
			temp = end->word;
			value = ft_dollar_eval(token, dict); 
		 	end->word = ft_strjoin(temp, value);		
			free (temp);
			free (value);
		}
		 if (!end->word)
                        ft_free_words(word);
	}
}		
	

char **min_dollar_asteriks_eval(t_lexer **token, t_dict *dict)
{
	char		**values;
	t_expander	*words;
		

	words = NULL;
	while (*token && min_token_is_word((*token)->key))
	{
		if (min_token_is_word() != 3) 		
			ft_add_value_to_word(&words, *token);
		else
			ft_add_asterisk(&words, *token);	
		*token = (*token)->next;
		if (!words)
			break; 
	}
	if (words && words->value == l_asterisk || words->next)
		values = ft_get_values(words, true);
	else
		values = ft_get_values(words, false);
	ft_free_words(&words);
	return (values);
}	
