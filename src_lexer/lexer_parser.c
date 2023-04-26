/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:24:19 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/26 15:53:54 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int write_key_and_value_to_token(t_lexer *token, t_lexertype key, char *input, int len)
{
	if (len > 0)
	{
		token->key = key;
		token->value = ft_substr(input, 0, len);
		if (!token->value)
			return (-1);
	}
	return (0);
}

static int dollar_find_next_token_pos(char *input, int pos)
{
	int i;
	t_lexertype next_token;
	
	i = 0;
	while (input[pos] != '\0')
	{
		next_token = check_token(input[pos], input[pos + 1]);
		if (next_token == l_dollar)
		{
			pos++;
			break;
		}
		if (next_token == l_word)
			pos++;
		else
			break ;
	}
	return (pos);
}

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


int parse_dollar(char *input, int pos, t_lexer *tmp)
{
	//int i;
	int len;
	int start;
	t_lexertype next_token;

	start = pos - 1;
	pos = dollar_find_next_token_pos(input, pos);
	len = pos - start;
	write_key_and_value_to_token(tmp, l_dollar, input + start, len);
	return (pos);
}

/*
empty quotes are not working yet!!! again :((
*/

static int quote_find_next_token_pos(char *input, int pos, t_lexertype token)
{
	int dollar_flag;
	int i;
	t_lexertype next_token;

	i = 0;
	while (input[pos] != '\0')
	{
		next_token = check_token(input[pos], input[pos + 1]);
		if (next_token == token)
			break;
		else
			pos++;
		if (token == l_dquote && next_token == l_dollar)
			dollar_flag = 1;
	}
	return (pos);
}

static int check_if_dollar_occurrs_in_dquote(char *input, int start, int pos, t_lexertype token)
{
	t_lexertype next_token;
	int dollar_flag;
	int i;
	
	i = 0;
	dollar_flag = 0;
	while (i < pos)
	{
		next_token = check_token(input[start + i], input[start + 1 + i]);
		if (token == l_dquote && next_token == l_dollar)
			dollar_flag = 1;
		i++;
	}
	return (dollar_flag);
}

int parse_quote(char *input, int pos, t_lexer *tmp, t_lexertype token)
{
	t_lexertype key;
	int i;
	int len;
	int start;
	int dollar_flag;

	start = pos;
	i = 0;
	pos = quote_find_next_token_pos(input, pos, token);
	len = pos - start;
	dollar_flag = check_if_dollar_occurrs_in_dquote(input, start, pos, token);
	if (dollar_flag == 1)
		key = l_dollar;
	else
		key = l_word;
	write_key_and_value_to_token(tmp, key, input + start, len);
	if (input[pos] == '\0')
		return (- token);
	return (pos + 1);
}

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
		next_token = check_token(input[pos], input[pos + 1]);
		if (next_token != l_word)
			break;
		else
			pos++;
	}
	len = pos - start;
	write_key_and_value_to_token(tmp, l_word, input + start, len);
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
