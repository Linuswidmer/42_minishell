/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:06:39 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/11 10:02:45 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quote_find_next_token_pos(char *input, int pos, t_lexertype token)
{
	int			i;
	t_lexertype	next_token;

	i = 0;
	while (input[pos] != '\0')
	{
		next_token = check_token(input, pos);
		if (next_token == token)
			break ;
		else
			pos++;
	}
	return (pos);
}

static int	check_if_dollar_occurrs_in_dquote(char *input, int start,
												int pos, t_lexertype token)
{
	t_lexertype	next_token;
	int			dollar_flag;
	int			i;

	i = 0;
	dollar_flag = 0;
	while (i < pos)
	{
		next_token = check_token(input, start + i);
		if (token == l_dquote && next_token == l_dollar)
			dollar_flag = 1;
		i++;
	}
	return (dollar_flag);
}

int	parse_quote(char *input, int pos, t_lexer *tmp, t_lexertype token)
{
	t_lexertype	key;
	int			i;
	int			len;
	int			start;
	int			dollar_flag;

	start = pos;
	i = 0;
	pos = quote_find_next_token_pos(input, pos, token);
	len = pos - start;
	dollar_flag = check_if_dollar_occurrs_in_dquote(input, start, pos, token);
	if (dollar_flag == 1)
		key = l_dollar;
	else
		key = l_word;
	key_value_to_token(tmp, key, input + start, len);
	if (input[pos] == '\0')
		return (-token);
	return (pos + 1);
}
