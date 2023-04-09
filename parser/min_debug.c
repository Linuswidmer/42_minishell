/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:12:46 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/07 19:49:06 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

char *lexertype1_names[] =
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
char *lexertype2_names[] =
{
    "EMPTY",
    "DQUOTE",
    "QUOTE",
    "WORD",
    "*",
    "( ",
    " )",
    "<< ",
    ">> ",
    "< ",
    "> ",
    "$",
    " && ",
    " || ",
    ";",
    " | ",
    "ESCAPE"
};




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
		printf(" %s | %s %s |", lexertype1_names[io->value], lexertype2_names[io->value],  io->file);		
		io = io->next;
	}
}



void min_print_cmd (t_cmdnode *cmd)
{
	 while (cmd)
    {
        printf("%s ", cmd->arg);
        cmd = cmd->next;
    }
}



void	min_print_jobnode(t_jobnode *job)
{
	min_print_io(job->in);
	min_print_cmd(job->cmd);
	min_print_io(job->out);
}	
		

void min_print_ast(void)
{
	char	horizental;

	horizental = 1;
	while (1)
	{
		if ((*ast)->key == jobnode)
      		{
			min_print_jobnode((*ast)->node.job);
            		if ((*ast)->node.job->up)
			{
                		*ast = (*ast)->node.job->up;
				
			}	
            		else
                		break;
        }
        if ((*ast)->key == subnode)
        {
            if ((*ast)->node.sub->up)
                *ast = (*ast)->node.sub->up;
            else
                break;
        }
        if ((*ast)->key == pipenode)
        {
            if ((*ast)->node.pipe->prev)
                *ast = (*ast)->node.pipe->prev;
            else if ((*ast)->node.pipe->up)
                *ast = (*ast)->node.pipe->up;
            else
                break;
        }
        if ((*ast)->key == routenode)
        {
            if ((*ast)->node.route->prev)
                *ast = (*ast)->node.route->prev;
            else if ((*ast)->node.route->up)
                *ast = (*ast)->node.route->up;
            else
                break;

		





}
