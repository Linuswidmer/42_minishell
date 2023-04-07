/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:43:16 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/07 09:43:27 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void expand_dollar_tokens(t_lexer *first)
{
	char *varname;

	while (first)
	{
		if (first->key == l_dollar)
		{
			first->key = l_word;
			varname = first->value;
			first->value = ft_strdup("content");
			free(varname);
		}
		first = first->next;
	}
}
