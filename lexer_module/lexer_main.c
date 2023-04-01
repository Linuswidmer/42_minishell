/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:54:21 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/01 18:37:54 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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
    "AND",
    "OR",
    "SEMI",
    "PIPE",
    "ESCAPE"
};

t_lexertype check_lexertype(char c, char next)
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
	else if (c == '&' && next == '&')
		return (AND);
	else if (c == '|' && next == '|')
		return (OR);
	else if (c == ';')
		return (SEMI);
	else if (c == '|')
		return (PIPE);
	else if (c == 92)
		return (ESCAPE);
	else	
		return (WORD);
}

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

t_lexer *lexer_parser(char *input)
{
	int i;
	t_lexertype current_lexer_key;
	t_lexertype previous_lexer_key;
	t_lexer *tmp;
	t_lexer *tmp2;
	t_lexer *first;
	
	i = 0;
	tmp = init_lexer_struct();
	current_lexer_key = EMPTY;
	previous_lexer_key = EMPTY;
	first = tmp;
	tmp->key = check_lexertype(input[0], input[1]);
	current_lexer_key = check_lexertype(input[0], input[1]);
	while (input[i] != '\0')
	{
		if (input[i] == ' '&& previous_lexer_key != 1 && previous_lexer_key != 2)
		{
					previous_lexer_key = current_lexer_key;
					current_lexer_key = EMPTY;
		}
		else if (tmp->key != current_lexer_key || tmp->key != check_lexertype(input[i], input[i + 1]))
		{
			tmp2 = init_lexer_struct();
			tmp->next = tmp2;
			tmp2->prev = tmp;
			tmp2->key = check_lexertype(input[i], input[i + 1]);
			previous_lexer_key = current_lexer_key;
			current_lexer_key = check_lexertype(input[i], input[i + 1]);
			tmp = tmp2;
			printf("NEW LEXERTYPE at position: %i, VALUE IS %i\n", i, tmp->key);
		}
		i++;
	}
	return (first);
}

void print_lexer_list(t_lexer *first)
{
	t_lexer *tmp;

	tmp = first;
	while (tmp)
	{
		printf("LEXERTYPE IS: %s\n", lexertype_names[tmp->key]);
		tmp = tmp->next;
	}
}

int main(int argc, char **argv)
{
	t_lexer *first;

	//printf("%s\n", argv[1]);
	first = lexer_parser(argv[1]);
	print_lexer_list(first);	
}
