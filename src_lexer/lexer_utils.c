/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 10:04:52 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/02 11:11:09 by lwidmer          ###   ########.fr       */
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
	"TIL",
	"DOLLAR_Q"
};

int	skip_space_tab(char *input, int pos)
{
	while (input[pos] == ' ' || input[pos] == 9)
		pos++;
	return (pos);
}

t_lexer	*init_lexer_struct(void)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->key = l_empty;
	lexer->value = NULL;
	lexer->next = NULL;
	lexer->prev = NULL;
	return (lexer);
}

void	print_token_list(t_lexer *first)
{
	t_lexer	*tmp;

	tmp = first;
	while (tmp)
	{
		ft_printf_fd("LEXERTYPE IS: %s	",2, lexertype_names[tmp->key]);
		ft_printf_fd("STRING IS *%s*\n",2, tmp->value);
		tmp = tmp->next;
	}
	ft_printf_fd("\n", 2);
}
