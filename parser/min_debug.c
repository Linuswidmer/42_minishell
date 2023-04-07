/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:12:46 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/07 18:13:32 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

char *lexertypes_names[] =
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




void min_print_io(t_ionode *io)
{
	while (io)
	{
		printf("%s		", lexertypes_names[io->value]);
		printf("%s		", io->file);		
		io = io->next;
	}
}



void min_print_cmd (t_cmdnode *cmd)
{
	 while (cmd)
    {
        printf("%s      ", cmd->arg);
        cmd = cmd->next;
    }
}

void min_print_ast(void)
{

}
