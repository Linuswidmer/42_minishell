/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:12:46 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/07 17:39:32 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"


char *nodetype_names[] =
{
    "ROUTENODE",
    "PIPENODE",
    "JOBNODE",
    "SUBNODE"
};

void min_print_io(t_ionode *io)
{
	while (io)
	{
		printf("%s		", lexertype_names[io->value]);
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
