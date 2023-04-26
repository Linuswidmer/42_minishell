/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:40:31 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/26 14:40:40 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer *add_to_token_list(t_lexer *list_end, t_lexertype key, char *str, int start, int pos)
{
	t_lexer *new_list_end;

	new_list_end = init_lexer_struct();
	new_list_end->prev = list_end;
	list_end->next = new_list_end;
	list_end->key = key;
	if (str)
		list_end->value = ft_substr(str, start, pos - start);
	return (new_list_end);
}

t_lexer *remove_token_from_list_end(t_lexer *list_end)
{
	t_lexer *new_list_end;

	new_list_end = list_end->prev;
	new_list_end->next = NULL;
	if (list_end->value)
		free(list_end->value);
	free(list_end->value);
	free(list_end);
	return (new_list_end);
}
