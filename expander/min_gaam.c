/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_gaam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:48:07 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/22 18:46:18 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_word(t_lexer **token, t_expander **asterisk, char *value)
{
	t_expander	*end;
	char		*temp;

	end = min_last_expander(*asterisk);
	if (end->key == l_asterisk)
	{
		end->next = min_init_expander(l_word, ft_strdup(EMPTY));
		if (!end->next)
			min_free_expander(asterisk);
		else
			end = end->next;
	}
	temp = end->word;
	if (!value)
		end->word = ft_strjoin(temp, (*token)->value);
	else
		end->word = ft_strjoin(temp, value);
	min_free(&temp);
	*token = (*token)->next;
}

/* decide t_exphelp   */
static char	ft_dollar(t_lexer **token, t_expander **asterisk,
								t_expander **extra, t_dict *dict)
{
	t_expander	*dollar;
	t_exphelp	help;

	dollar = *asterisk;
	help = min_init_exphelp(dict, 0, 0);
	help.space = min_dollar(token, &dollar, extra, help);
	if (!dollar)
		min_free_expander(asterisk);
	else
		*asterisk = dollar;
	return (help.space);
}

static void	ft_asterisk(t_lexer **token, t_expander **asterisk)
{
	t_expander	*end;

	end = min_last_expander(*asterisk);
	end->next = min_init_expander(l_asterisk, ft_strdup(EMPTY));
	if (!end->next)
		min_free_expander(asterisk);
	*token = (*token)->next;
}

char	min_gaam(t_lexer **token, t_expander **asterisk, t_expander **extra,
			t_dict *dict)
{
	char	space;

	space = 0;
	*token = (*token)->next;
	*extra = min_init_expander(l_empty, ft_strdup(EMPTY));
	if (!extra)
		return (space);
	while (!space && (*extra)->key == l_empty && asterisk && *token
		&& min_token_is_word((*token)->key))
	{
		if (min_token_is_word((*token)->key) == 1)
			ft_word(token, asterisk, NULL);
		else if (min_token_is_word((*token)->key) == 2)
			space = ft_dollar(token, asterisk, extra, dict);
		else if (min_token_is_word((*token)->key) == 4)
			ft_word(token, asterisk, TIL);
		else
			ft_asterisk(token, asterisk);
	}
	return (space);
}
