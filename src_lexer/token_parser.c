/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:24:19 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/07 23:43:38 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int parse_token(char *input, int pos, t_lexer *tmp, t_lexertype token_type, int (*find_next_token_pos)(char *, int))
{
    int len;
    int start;
    start = pos - 1;
    pos = find_next_token_pos(input, pos);
    len = pos - start;
    write_key_and_value_to_token(tmp, token_type, input + start, len);
    return pos;
}
*/

int parse_double_tokens(char *input, int pos, t_lexertype token, t_lexer *tmp)
{
  tmp->key = token;
	return (pos + 1);
}

int parse_single_tokens(t_lexer *tmp, t_lexertype token, int pos)
{
  tmp->key = token;
  return (pos);
}

int parse_word(char *input, int pos, t_lexer *tmp)
{
	t_lexertype next_token;
	int start;
	int len;

	start = pos - 1;
	while (input[pos] != '\0')
	{
		next_token = check_token(input, pos);
		if (next_token != l_word)
			break;
		else
			pos++;
	}
	len = pos - start;
	key_value_to_token(tmp, l_word, input + start, len);
	return (pos);
}

int parse_token_to_list(t_lexertype current_token, char *input, int pos, t_lexer *tmp, int start)
{
	pos++;
	if (current_token == l_quote || current_token == l_dquote)
		return (parse_quote(input, pos, tmp, current_token));
	else if(current_token == l_dollar)
		return (parse_dollar(input, pos, tmp));
	else if (current_token == l_or || current_token == l_and 
        || current_token == l_heredoc || current_token == l_append)
		return (parse_double_tokens(input, pos, current_token, tmp));
	else if (current_token == l_word)
		return (parse_word(input, pos, tmp));
	else
		return (parse_single_tokens(tmp, current_token, pos));
}
