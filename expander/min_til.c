/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_til.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:40:07 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/22 13:02:41 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_til_in_dict(t_dict *dict)
{
	while (dict)
	{
		if (ft_strncmp(dict->key, HOME, ft_strlen(HOME)))
			dict = dict->next_entry;
		else
			break ;
	}
	if (!dict)
		return (NULL);
	else
		return (dict->value);
}

static char	*ft_eval_til(t_lexer *token, t_exphelp help)
{
	if ((!token->prev || !min_token_is_word(token->prev->key))
		&& (!token->next || !min_token_is_word(token->next->key)))
	{	
		help.value = ft_strdup(ft_til_in_dict(help.dict));
		if (!help.value)
			help.value = ft_strdup(EMPTY);
	}	
	else
		help.value = ft_strdup(TIL);
	return (help.value);
}

static t_expander	*ft_til_start(t_expander **word)
{
	t_expander	*end;	

	if ((*word)->key == l_empty)
	{
		(*word)->key = l_word;
		end = *word;
	}
	else
		end = min_last_expander(*word);
	return (end);
}

char	min_til(t_lexer **token, t_expander **word, t_exphelp help)
{
	t_expander	*end;

	help.value = ft_eval_til(*token, help);
	end = ft_til_start(word);
	if (end)
	{
		help.dollar_value = end->word;
		if (help.dollar_value)
			end->word = ft_strjoin(help.dollar_value, help.value);
		else
			end ->word = ft_strdup(help.value);
		//min_free(temp);
		//min_free(value);
	}
	if (!end || !end->word)
		min_free_expander(word);
	if (*token)
		*token = (*token)->next;
	return (0);
}
