/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:00:18 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/22 18:35:36 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	ft_special_next_token(t_lexer **token, t_expander **word,
										t_expander **extra, t_exphelp help)
{
	if (!(*token) || (*token && !min_token_is_word((*token)->key)))
	{
		if (extra)
			return (min_to_aste(word, min_init_expander(l_word,
						ft_strdup(DOLLAR)), token));
		min_word(NULL, word, DOLLAR, help.space);
		return (1);
	}
	else if ((*token)->key == l_dollar)
	{
		ft_putstr_fd(ERR_ID, 2);
		if (extra)
			return (min_to_aste(word, min_init_expander(l_word,
						ft_strdup(DDOLLAR)), token));
		return (min_word(token, word, DDOLLAR, help.space));
	}
	else if ((*token)->key == l_til)
	{
		if (extra)
			return (min_to_aste(word, min_init_expander(l_word, ft_strdup(DTIL)), token));
		return (min_word(token, word, DTIL, help.space));
	}
	return (help.space);
}

static int	ft_next_is_special(t_lexer **token)
{
	if (!(*token) || (*token && !min_token_is_word((*token)->key)))
		return (1);
	else if ((*token)->key == l_dollar)
		return (1);
	else if ((*token)->key == l_til)
		return (1);
	else
		return (0);
}

/* if token->next is no word or DOLLAR or Til */
char	min_dollar(t_lexer **token, t_expander **word, t_expander **extra,
							t_exphelp help)
{
	if ((*token)->value[0] == E_QUOTE)
		help.export = 1;
	(*token) = (*token)->next;
	if (ft_next_is_special(token))
		return (ft_special_next_token(token, word, extra, help));
	else if ((*token)->key == l_asterisk)
	{
		*token = (*token)->next;
		return (help.space);
	}	
	else
		return (min_eval_dollar(token, word, extra, help));
}
