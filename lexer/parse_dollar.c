/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:04:33 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/22 09:53:17 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dollar_find_next_token_pos(char *input, int pos)
{
	int			i;
	t_lexertype	next_token;

	i = 0;
	while (input[pos] != '\0')
	{
		next_token = check_token(input, pos);
		if (next_token == l_dollar)
			return (pos + 1);
		if (next_token == l_paraopen)
		{
			while (input[pos] != '\0')
			{
				if (check_token(input, pos) == l_paraclose)
					return (pos + 1);
				pos++;
			}
		}
		if (next_token == l_word)
			pos++;
		else
			break ;
	}
	return (pos);
}

/*
adds a new entry to token list of type l_dollar and writes the word that occurs
behind the dollar in the value of the token list.
helper function dollar_find_next_token_pos is required, since the word behind
the dollar can be terminated when a space occurs, a dollar occurs etc... 
*/
int	parse_dollar(char *input, int pos, t_lexer *tmp)
{
	int			len;
	int			start;

	start = pos - 1;
	if (input[pos] == '"' || input[pos] == 39)
		return (pos);
	pos = dollar_find_next_token_pos(input, pos);
	len = pos - start;
	key_value_to_token(tmp, l_dollar, input + start, len);
	return (pos);
}
