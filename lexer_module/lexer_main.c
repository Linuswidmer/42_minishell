/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:54:21 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/04 15:04:25 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer *init_lexer_struct()
{
	t_lexer *lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->key = EMPTY;
	lexer->value = NULL;
	lexer->next = NULL;
	lexer->prev = NULL;
	return(lexer);
}

char *lexertype_names[] = 
{
	"EMPTY",
    "DQUOTE",
    "QUOTE",
    "WORD",
    "ASTERISK",
    "PAROPEN",
    "PARCLOSE",
    "HEREDOC",
    "APPEND",
    "IN",
    "OUT",
    "DOLLAR",
    "AND",
    "OR",
    "SEMI",
    "PIPE",
    "ESCAPE"
};

int skip_space_tab(char *input, int pos)
{
	while (input[pos] == ' ' || input[pos] == 9)
		pos++;
	return (pos);
}

void expand_dollar_tokens(t_lexer *first)
{
	char *varname;

	while (first)
	{
		if (first->key == DOLLAR)
		{
			first->key = WORD;
			varname = first->value;
			first->value = ft_strdup("content");
			free(varname);
		}
		first = first->next;
	}
}

t_lexer *lexer(char *input)
{
  int start;
  int pos;
  int len_input;
  t_lexertype current_token;
  t_lexer *tmp;
  t_lexer *tmp2;
  t_lexer *beginning_token_list;

	beginning_token_list = init_lexer_struct();
	tmp = beginning_token_list;
	start = 0;
	pos = 0;
	len_input = ft_strlen(input);
  while (pos < len_input)
  {
    current_token = check_token(input[pos], input[pos + 1]);
    pos = parse_token_to_list(current_token, input, pos, tmp, start);
    pos = skip_space_tab(input, pos);
    start = pos;
    if (tmp->key != EMPTY && pos < len_input)
    {
      tmp2 = init_lexer_struct();
      tmp->next = tmp2;
      tmp2->prev = tmp;
      tmp = tmp2;
    }
  }
  return(beginning_token_list);
}


void print_token_list(t_lexer *first)
{
	t_lexer *tmp;

	tmp = first;
	while (tmp)
	{
		printf("LEXERTYPE IS: %s	", lexertype_names[tmp->key]);
		printf("STRING IS *%s*\n", tmp->value);
		tmp = tmp->next;
	}
}

void free_token_list(t_lexer *token_list)
{
  t_lexer *tmp;

  while (token_list)
  {
    tmp = token_list->next;
    if (token_list->value)
      free (token_list->value);
    free(token_list);
    token_list = tmp;
  }
}

int main(int argc, char **argv)
{
	t_lexer *first;
	char my_string[100]; 
  char *readline_input;
  t_lexer *token_list;

  while (1)
  {
	  readline_input = readline("minishell> ");
    token_list = lexer(readline_input);
    print_token_list(token_list);
    free(readline_input);
  }
 //  first = lexer(argv[1]);
	// print_token_list(first);
  // free_token_list(first);
  if (argc == 1)
  {
	  first = lexer(my_string);
	  print_token_list(first);
  }
  // check_token_list(first);
}
