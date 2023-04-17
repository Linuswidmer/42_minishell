/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_word_eval.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:38:59 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/17 11:05:50 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	ft_asterisk(t_lexer **token, t_expander **word)
{	
	t_expander	*end;
	
	if ((*word)->key == l_empty)
		(*word)->key = l_asterisk;
	else
	{	
		end = min_last_expander(*word);
		if (end->key != l_asterisk)
			end->next = min_init_expander(l_asterisk); 	
		if (!end->next)
			min_free_expander(word);
	}
	*token = (*token)->next;
} 	

char **ft_get_values(t_expander *word)
{
	char **values;
	char *temp;
	if (!word)
		return (NULL);
	values = (char **)malloc(sizeof(values) * 2);
	if (!values)
		return (NULL)
	temp = ft_strdup((const char *)word->word);
	if (temp)
		values[0] = temp;
		values[1] = NULL;
	else
	{
		free(values);
		values = NULL;
	} 
	return (values);	
}


char **min_word_eval(t_lexer **token, t_dict *dict)
{
	char	**values;
	t_expander	*word;
	
	word = min_init_expander(l_empty);
	while (word && *token && min_token_is_word((*token)->key))
	{
		if (min_token_is_word((*token)->key) == 1)
			min_word(token, &word);
		else if (min_token_is_word((*token)->key) == 2)
			min_dollar(token, &word, dict);
		else
			ft_asterisk(token, &word);
	}
	if (word && (word->value == l_asterisk || word->next))
		values = min_asterisk(word);
	else
		values = ft_get_values(word);
	min_free_expander(&word);
	return (values);
}
