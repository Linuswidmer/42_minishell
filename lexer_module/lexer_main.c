/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:54:21 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/03 16:57:28 by lwidmer          ###   ########.fr       */
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
	"DOLLAR",
    "AND",
    "OR",
    "SEMI",
    "PIPE",
    "ESCAPE"
};

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] != '\0')
		i++;
	return (i);
}

t_lexertype check_lexertype(char c)
{
	char next;

	next = 0;
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

t_lexertype evaluate_token_arr(t_lexertype *token_arr)
{
	if (token_arr[0] == QUOTE || token_arr[0] == DQUOTE)
		return (token_arr[0]);
	else if (token_arr[0] == SEMI)
	{
		if (token_arr[1] != SEMI && token_arr[1] != PIPE && token_arr[1] != AND)
			return (token_arr[0]);
		else
			perror("parse error near ...");
	}
	return (token_arr[0]);
}

t_lexertype get_lexertype(char *input, int pos)
{
	t_lexertype token_arr[3];
	t_lexertype token;
	
	token_arr[0] = check_lexertype(input[pos]);
	token_arr[1] = check_lexertype(input[pos + 1]);
	token_arr[2] = check_lexertype(input[pos + 2]);
	token = evaluate_token_arr(token_arr);
	return (token_arr[0]);
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

int skip_whitespaces(char *input, int pos)
{
	while (input[pos] == ' ')
		pos++;
	return (pos);
}

int find_next_lexertype_position(char *input, int pos, t_lexertype current_lexertype, t_lexertype OPENQUOTE)
{
	t_lexertype next_lexertype;

	while (input[pos] != '\0')
	{
		next_lexertype = get_lexertype(input, pos);
		if (OPENQUOTE == QUOTE)
		{
			if (next_lexertype == QUOTE)
				return (pos);
			else
				pos++;
		}
		else 
		{
			if (input[pos] == ' ')
				return (pos);
			else if (next_lexertype != current_lexertype)
				return (pos);
			else
				pos++;
		}
	}
	return (pos);
}
	
void lexer_parser(t_lexer *tmp, t_lexertype current_lexertype, char *input, int start, int end)
{
	int i;
	int j;
	
	i = start;
	j = 0;
	tmp->value = malloc(sizeof(char) * end - start + 1);
	//printf("start is %i, end is %i", start, end);
	//printf(" LEXERTYPE IS %s\n", lexertype_names[current_lexertype]);
	while (start <= end - 1)
	{
		tmp->value[j] = input[start];
		j++; 
		start++;
	}
	tmp->value[j] = '\0';
}

t_lexer *lexer(char *input)
{
	int start;
	int pos;
	int len_input;
	t_lexer *tmp;
	t_lexer *tmp2;
	t_lexer *first;
	t_lexertype openquote;

	first = init_lexer_struct();
	tmp = first;

	openquote = 0;
	start = 0;
	pos = 0;
	len_input = ft_strlen(input);
	
	while (pos < len_input)
	{
		tmp->key = get_lexertype(input, pos);
		pos = find_next_lexertype_position(input, pos, tmp->key, openquote);
		if (openquote == EMPTY)
		{
			if (tmp->key == QUOTE)
				openquote = QUOTE;
			else if(tmp->key == DQUOTE)
				openquote = DQUOTE;
		}
		else if (openquote == QUOTE && tmp->key == QUOTE)
		{
			openquote = 0;
			pos++;
		}
		else if (openquote == DQUOTE && tmp->key == DQUOTE)
		{
			openquote = 0;
			pos++;
		}
		lexer_parser(tmp, tmp->key, input, start, pos);
		pos = skip_whitespaces(input, pos);
		start = pos;
		tmp2 = init_lexer_struct();
		tmp->next = tmp2;
		tmp2->prev = tmp;
		tmp = tmp2;
	}
	return (first);
}

void print_lexer_list(t_lexer *first)
{
	t_lexer *tmp;

	tmp = first;
	while (tmp)
	{
		printf("LEXERTYPE IS: %s	", lexertype_names[tmp->key]);
		printf("STRING IS $%s$\n", tmp->value);
		tmp = tmp->next;
	}
}

int main(int argc, char **argv)
{
	t_lexer *first;
	char my_string[100]; 
	my_string[0] = 'H';
	my_string[1] = 'e';
	my_string[2] = 'l';
	my_string[3] = 'l';
	my_string[4] = 'o';
	my_string[5] = ' ';
	my_string[6] = '$';
	my_string[7] = '\0';	

	//printf("%s\n", argv[1]);
	//first = lexer_parser(argv[1]);
	first = lexer(argv[1]);
	print_lexer_list(first);
}
