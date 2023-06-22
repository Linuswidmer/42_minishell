/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_to_aste.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:02:56 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/22 13:04:43 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	min_to_aste(t_expander **word, t_expander *new, t_lexer **token)
{
	char	*oldword;

	if ((new && new->key == l_word) && (*word
			&& (min_last_expander(*word))->key == l_word))
	{
		oldword = (min_last_expander(*word))->word;
		(min_last_expander(*word))->word = ft_strjoin(oldword, new->word);
		min_free(&oldword);
		(min_last_expander(*word))->next = new->next;
	}
	else if (*word)
	{
		(min_last_expander(*word))->next = new;
	}
	if (token)
		(*token) = (*token)->next;
	return (0);
}
