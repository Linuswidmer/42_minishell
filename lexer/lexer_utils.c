/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 10:04:52 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/22 09:45:28 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/04/07 17:50:52 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_space_tab(char *input, int pos)
{
	while (input[pos] == ' ' || input[pos] == 9)
		pos++;
	return (pos);
}

t_lexer	*init_lexer_struct(void)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->key = l_empty;
	lexer->value = NULL;
	lexer->next = NULL;
	lexer->prev = NULL;
	return (lexer);
}
