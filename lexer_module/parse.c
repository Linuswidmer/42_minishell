#include "lexer.h"

int parse_dollar(char *input, int pos, t_lexer *tmp, int start)
{
  int i;
	t_lexertype next_token;

	tmp->key = DOLLAR;
	start++;
  i = 0;
  while (input[pos] != '\0')
  {
    next_token = check_token(input[pos], input[pos + 1]);
		if (next_token == WORD && ft_isalnum(input[pos]))
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
  int end;

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
  end = pos - 1;
  if (end - start >= 0)
  {
    tmp->key = WORD;
    tmp->value = ft_substr(input, start, end);
  }
  return (pos + 1);
}

int parse_double_tokens(char *input, int pos, t_lexertype current_token, t_lexer *tmp)
{
  tmp->key = current_token;
	return (pos + 1);
}

int parse_single_tokens(t_lexer *tmp, t_lexertype current_token, int pos)
{
  tmp->key = current_token;
  return (pos);
}

int parse_word(char *input, int pos, t_lexer *tmp, int start)
{
  t_lexertype next_token;

  tmp->key = WORD;
  while (input[pos] != '\0')
  {
		next_token = check_token(input[pos], input[pos + 1]);
		if (next_token != WORD || input[pos] == ' ')
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
  if (current_token == QUOTE || current_token == DQUOTE)
    return (parse_quote(input, pos, tmp, start, current_token));
	else if(current_token == DOLLAR)
    return (parse_dollar(input, pos, tmp, start));
	else if (current_token == OR || current_token == AND 
        || current_token == HEREDOC || current_token == APPEND)
		return (parse_double_tokens(input, pos, current_token, tmp));
	else if (current_token == WORD)
		return (parse_word(input, pos, tmp, start));
	else
	  return (parse_single_tokens(tmp, current_token, pos));
}
