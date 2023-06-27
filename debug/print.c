/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:14:59 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/27 13:47:31 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
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

void    print_token_list(t_lexer *first)
{
    t_lexer *tmp;
	//char *lexertype_names = NULL;

    tmp = first;
    while (tmp)
    {
        ft_printf_fd("LEXERTYPE IS: %s  ",2, lexertype_names[tmp->key]);
        ft_printf_fd("STRING IS *%s*\n",2, tmp->value);
        tmp = tmp->next;
    }
    ft_printf_fd("\n", 2);
}*/

void	print_token_list(t_lexer *first)
{
	(void)first;
	t_printf_fd("NO_DEBUG\n", 2);
}
