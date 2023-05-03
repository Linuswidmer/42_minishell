/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 10:04:52 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/03 09:21:02 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/04/07 17:50:52 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    "ESCAPE",
	"SPACE",
	"AMP",
	"TIL"
};

int ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v')
		return (1);
	else
		return (0);
}

int skip_space_tab(char *input, int pos)
{
	while (input[pos] == ' ' || input[pos] == 9)
		pos++;
	return (pos);
}

t_lexer *init_lexer_struct()
{
	t_lexer *lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->key = l_empty;
	lexer->value = NULL;
	lexer->next = NULL;
	lexer->prev = NULL;
	return(lexer);
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



