/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_add_io_to_sub.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:04:41 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/23 16:14:35 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_token_not_valid(t_lexer **token, t_ast **ast, char *io)
{
	if (min_token_is_io((*token)->key) == 2 && !*io)
	{
		if (min_heredoc(token, HEREDOC))
			return (min_heredoc_fail(ast));
	}
	else if (min_token_is_io((*token)->key))
	{
		if (!*io)
			*io = 1;
		else
			return (min_parser_error(ast, (*token)->key, NULL));
	}
	else if (min_token_is_word((*token)->key) && *io)
		*io = 0;
	else if (min_token_is_word((*token)->key) && !*io)
		return (min_parser_error(ast, (*token)->key, (*token)->value));
	if ((*token)->next || !*io)
		return (0);
	else
		return (min_parser_error(ast, (*token)->key, P_NEWLINE));
}

/*    */
static t_lexer	*ft_find_last_token(t_lexer *token, t_ast **ast)
{
	char	io;

	io = 0;
	while (token)
	{
		if (min_token_is_jobnode(token->key))
		{
			if (ft_token_not_valid(&token, ast, &io))
				break ;
			token = token->next;
		}
		else
		{
			if (io)
				min_parser_error(ast, token->key, NULL);
			break ;
		}
	}
	return (token);
}

/*    */

t_lexer	*min_add_io_to_sub(t_lexer *token, t_ast **ast)
{
	if (min_token_is_word(token->key))
		min_parser_error(ast, token->key, token->value);
	else
	{
		(*ast)->u_no.sub->start = token;
		token = ft_find_last_token(token, ast);
		if (*ast)
			(*ast)->u_no.sub->last = token;
	}
	return (token);
}
