/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:54:21 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/04 13:00:34 by lwidmer          ###   ########.fr       */
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

int find_next_token_position(char *input, int pos, t_lexertype current_lexertype, t_lexertype openquote)
{
	t_lexertype next_token;

	pos++;
	while (input[pos] != '\0')
	{
		next_token = check_token(input[pos], input[pos + 1]);
		if (openquote == QUOTE && current_lexertype != QUOTE)
		{
			if (next_token == QUOTE)
				return (pos);
			else
				pos++;
		}
		else if(current_lexertype == DOLLAR)
		{
			if (next_token == WORD && ft_isalnum(input[pos]))
				pos++;
			else
				return (pos);
		}
		else 
		{
			if (input[pos] == ' ')
				return (pos);
			else if (next_token != current_lexertype)
			{
				if (current_lexertype == OR || current_lexertype == AND ||
					current_lexertype == HEREDOC || current_lexertype == APPEND)
				{
					return (pos + 1);
				}
				else
					return (pos);
			}
			else
				pos++;
		}
	}
	return (pos);
}

/*
writes key and string to the lexer linked list and directly returns a new entry for the list.
*/
t_lexer *lexer_parser(t_lexer *tmp, t_lexertype current_lexertype, char *input, int start, int end)
{
	int i;
	int j;
	t_lexer *tmp2;
	
	i = start;
	j = 0;
	tmp->key = current_lexertype;
	if (tmp->key == DOLLAR)
		start++;
	tmp->value = malloc(sizeof(char) * end - start + 1);
	//printf("start is %i, end is %i", start, end);
	//printf(" LEXERTYPE IS %s\n", lexertype_names[current_lexertype]);
	while (start <= end)
	{
		tmp->value[j] = input[start];
		j++; 
		start++;
	}
	tmp->value[j] = '\0';
	tmp2 = init_lexer_struct();
	tmp->next = tmp2;
	tmp2->prev = tmp;
	return (tmp2);
}

t_lexertype lexer_quote_status(t_lexertype openquote, t_lexertype current_token, int *pos)
{
		if (openquote == EMPTY)
		{
			if (current_token == QUOTE)
				openquote = QUOTE;
			else if(current_token == DQUOTE)
				openquote = DQUOTE;
		}
		else if (openquote == QUOTE && current_token == QUOTE)
			openquote = 0;
		else if (openquote == DQUOTE && current_token == DQUOTE)
			openquote = 0;
	return (openquote);	
}

t_lexer *lexer(char *input)
{
	int start;
	int next_token_pos;
	int len_input;
	t_lexer *tmp;
	t_lexer *tmp2;
	t_lexer *first;
	t_lexertype current_token;
	t_lexertype openquote;

	first = init_lexer_struct();
	tmp = first;

	openquote = 0;
	start = 0;
	next_token_pos = 0;
	len_input = ft_strlen(input);
	
	while (next_token_pos < len_input)
	{
		current_token = check_token(input[next_token_pos], input[next_token_pos + 1]);
		next_token_pos = find_next_token_position(input, next_token_pos, 
			current_token, openquote);
		openquote = lexer_quote_status(openquote, current_token, &next_token_pos);
		tmp = lexer_parser(tmp, current_token, input, start, next_token_pos - 1);
		next_token_pos = skip_space_tab(input, next_token_pos);
		start = next_token_pos;
	}
	return (first);
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

t_lexer *remove_quotes_from_token_list(t_lexer *first)
{
	t_lexer *tmp;
	t_lexer *prev;
	t_lexer	*next;

	while (first->key == QUOTE || first->key == DQUOTE)
	{
		tmp = first->next;
		free(first);
		tmp->prev = NULL;
		first = tmp;
	}
	tmp = first;
	while (tmp)
	{
		if (tmp->key == QUOTE || tmp->key == DQUOTE)
		{
			prev = tmp->prev;
			next = tmp->next;
			prev->next = next;
			next->prev = prev;
			free(tmp);
			tmp = prev;
		}
		tmp = tmp->next;
	}
	return (first);
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

int main(int argc, char **argv)
{
	t_lexer *first;
	char my_string[100]; 
	my_string[0] = '$';
	my_string[1] = 'e';
	my_string[2] = 'l';
	my_string[3] = '!';
	my_string[4] = 'o';
	my_string[5] = ' ';
	my_string[6] = '$';
	my_string[7] = '\0';	

	//printf("%s\n", argv[1]);
	//first = lexer_parser(argv[1]);
	first = lexer(argv[1]);
	print_token_list(first);
	
	printf("After removing quotes\n");
	first = remove_quotes_from_token_list(first);
	print_token_list(first);
	printf("\n");
	first = lexer(my_string);
	expand_dollar_tokens(first);
	first = remove_quotes_from_token_list(first);
	print_token_list(first);
	check_token_list(first);
}
