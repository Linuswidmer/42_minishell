/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:13:58 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/04 13:14:14 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexertype check_double_tokens(char c, char next)
{
	if (c == '<' && next == '<')
		return (HEREDOC);
	else if (c == '>' && next == '>')
		return (APPEND);
	else if (c == '&' && next == '&')
		return (AND);
	else if (c == '|' && next == '|')
		return (OR);
	else
		return (EMPTY);
}

t_lexertype check_single_tokens(char c)
{
	if (c == 39)
		return (QUOTE);
	else if (c == '"')
		return (DQUOTE);
	else if (c == '*')
		return (ASTERISK);
	else if (c == '(')
		return (PAROPEN);
	else if (c == ')')
		return (PARCLOSE);
	else if (c == '<')
		return (IN);
	else if (c == '>')
		return (OUT);
	else if (c == '$')
		return (DOLLAR);
	else if (c == ';')
		return (SEMI);
	else if (c == '|')
		return (PIPE);
	else if (c == 92)
		return (ESCAPE);
	else	
		return (WORD);
}

t_lexertype check_token(char c, char next)
{
	t_lexertype token_key;

	token_key = check_double_tokens(c, next);
	if (token_key == EMPTY)
		token_key = check_single_tokens(c);
	return (token_key);
}
