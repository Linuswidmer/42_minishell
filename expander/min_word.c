/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:34:03 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/22 18:15:41 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_expander	*ft_find_last_entry(t_expander **word)
{
	t_expander	*end;

	if (!*word)
		*word = min_init_expander(l_empty, EMPTY);
	if (*word && (*word)->key == l_empty)
		end = *word;
	else
		end = min_last_expander(*word);
	return (end);
}

static int	ft_create_new_entry(t_lexer **token, t_expander *end,
		char *value, char space)
{
	char	*temp;

	if (space && end->key != l_empty)
	{
		end->next = min_init_expander(l_word, ft_strdup(EMPTY));
		if (!end->next)
			return (1);
		end = end->next;
	}
	if (end->key == l_empty)
		end->key = l_word;
	temp = end->word;
	if (value)
		end->word = ft_strjoin(temp, value);
	else
		end->word = ft_strjoin(temp, (*token)->value);
	min_free(&temp);
	if (!end->word)
		return (1);
	return (0);
}

/* join word to old word or create new instance of word */
char	min_word(t_lexer **token, t_expander **word, char *value, char space)
{
	t_expander	*end;

	end = ft_find_last_entry(word);
	if (end)
		if (ft_create_new_entry(token, end, value, space))
			min_free_expander(word);
	if (token)
		*token = (*token)->next;
	return (0);
}
