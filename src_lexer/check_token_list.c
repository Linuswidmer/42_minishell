/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:25:03 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/07 09:23:53 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int check_if_all_quotes_closed(t_lexer *token)
{
	t_lexertype openquote;
	t_lexertype current_token;	

	openquote = EMPTY;
	while (token)
	{
		current_token = token->key;
		if (openquote == EMPTY && current_token == QUOTE)
			openquote = QUOTE;
		else if (openquote == EMPTY && current_token == DQUOTE)
			openquote = DQUOTE;
		else if (openquote == QUOTE && current_token == QUOTE)
			openquote = EMPTY;
		else if (openquote == DQUOTE && current_token == DQUOTE)
			openquote = EMPTY;
		token = token->next;
	}
	return (openquote);
}

int check_token_list(t_lexer *token)
{
	int err_status;

	printf("\nTest if all quotes are closed\n");

	err_status = check_if_all_quotes_closed(token);
	if (err_status)
		printf("Not all quotes closed\n");
	else
		printf("All quotes closed\n");
	return (err_status);
}
*/
