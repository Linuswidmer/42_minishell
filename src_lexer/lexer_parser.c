/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:24:19 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/09 19:54:50 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int parse_dollar(char *input, int pos, t_lexer *tmp, int start)
{
  int i;
	t_lexertype next_token;

	tmp->key = l_dollar;
	start++;
  i = 0;
  while (input[pos] != '\0')
  {
    next_token = check_token(input[pos], input[pos + 1]);
		if (next_token == l_word && ft_isalnum(input[pos]))
			pos++;
		else
			return (pos);
  }
  tmp->value = ft_substr(input, start, pos);
	return (pos);
}

int parse_quote(char *input, int pos, t_lexer *tmp, int start, t_lexertype token)
{
	t_lexertype next_token;
  int i;
  int len;

  start++;
  i = 0;
  while (input[pos] != '\0')
  {
		next_token = check_token(input[pos], input[pos + 1]);
		if (next_token == token)
			break;
		else
			pos++;
  }
  len = pos - start;
  if (len - 1 >= 0)
  {
    tmp->key = l_word;
    tmp->value = ft_substr(input, start, len);
  }
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

int parse_word(char *input, int pos, t_lexer *tmp, int start)
{
  t_lexertype next_token;

  tmp->key = l_word;
  while (input[pos] != '\0')
  {
		next_token = check_token(input[pos], input[pos + 1]);
		if (next_token != l_word || input[pos] == ' ')
			break;
		else
			pos++;
  }
  tmp->value = ft_substr(input, start, pos - start);
  return (pos);
}


int parse_token_to_list(t_lexertype current_token, char *input, int pos, t_lexer *tmp, int start)
{
	pos++;
	if (current_token == l_quote || current_token == l_dquote)
		return (parse_quote(input, pos, tmp, start, current_token));
	else if(current_token == l_dollar)
		return (parse_dollar(input, pos, tmp, start));
	else if (current_token == l_or || current_token == l_and 
        || current_token == l_heredoc || current_token == l_append)
		return (parse_double_tokens(input, pos, current_token, tmp));
	else if (current_token == l_word)
		return (parse_word(input, pos, tmp, start));
	else
	  return (parse_single_tokens(tmp, current_token, pos));
}
