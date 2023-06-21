/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:14:59 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/21 16:18:22 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell"

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

    tmp = first;
    while (tmp)
    {
        ft_printf_fd("LEXERTYPE IS: %s  ",2, lexertype_names[tmp->key]);
        ft_printf_fd("STRING IS *%s*\n",2, tmp->value);
        tmp = tmp->next;
    }
    ft_printf_fd("\n", 2);
}
