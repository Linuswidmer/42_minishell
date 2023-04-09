/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:13:58 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/09 20:06:47 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexertype check_single_tokens(char c)
{
	if (c == 39)
		return (l_quote);
	else if (c == '"')
		return (l_dquote);
	else if (c == '*')
		return (l_asterisk);
	else if (c == '(')
		return (l_paraopen);
	else if (c == ')')
		return (l_paraclose);
	else if (c == '<')
		return (l_in);
	else if (c == '>')
		return (l_out);
	else if (c == ';')
		return (l_semi);
	else if (c == '|')
		return (l_pipe);
	else if (c == 92)
		return (l_escape);
	else	
		return (l_word);
}

t_lexertype check_double_tokens(char c, char next)
{
	if (c == '<' && next == '<')
		return (l_heredoc);
	else if (c == '>' && next == '>')
		return (l_append);
	else if (c == '&' && next == '&')
		return (l_and);
	else if (c == '|' && next == '|')
		return (l_or);
	else if (c == '$' && check_single_tokens(next) == l_word && next != '\0') 
		return (l_dollar);
	else
		return (l_empty);
}

t_lexertype check_token(char c, char next)
{
	t_lexertype token_key;

	token_key = check_double_tokens(c, next);
	if (token_key == l_empty)
		token_key = check_single_tokens(c);
	return (token_key);
}
