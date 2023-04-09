/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:12:46 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/09 16:37:00 by jstrotbe         ###   ########.fr       */
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
	//printf("JOBNODE: ");
	min_print_io(job->in);
	min_print_cmd(job->cmd);
	min_print_io(job->out);
	//printf("\n");
}	


void	min_print_subnode(char vt)
{
	//printf("SUBNODE: ");
	if (vt)
		printf(")");
	else
		printf("(");
	//printf("\n");

}	

void	min_print_pipenode(void)
{
	printf(" | ");
}


void	min_print_routenode(char *rvalue)
{
	printf(" %s ", rvalue);
}

void min_print_ast(void)
{
	char	vt;
	char	ht;

	vt = 0;
	ht = 0;
	printf("\n START AST \n");
	while (1)
	{
		if ((*ast)->key == jobnode)
      	{
			min_print_jobnode((*ast)->node.job);
			vt = 1;
			if ((*ast)->node.job->up);
				*ast = (*ast)->node.job->up;
            else
				break;
		}
        if ((*ast)->key == subnode)
        {	
			min_print_subnode(vt);
            if ((*ast)->node.sub->up && vt)
                *ast = (*ast)->node.sub->up;
            else if (!vt)
        		*ast = (*ast)->node.sub->down;       	
			else
				break;		
        }
        if ((*ast)->key == pipenode)
        {
			if (vt && (*ast)->node.pipe->next)
			{
				min_print_pipenode();
				*ast = (*ast)->node.pipe->next;
				vt = 0;
			}
			else if (!vt)
                *ast = (*ast)->node.pipe->down;
            else 
			{
				while ((*ast)->node.pipe->prev)
            		*ast = (*ast)->node.pipe->prev;
				if ((*ast)->node.pipe->up)
					*ast = (*ast)->node.pipe->up;
				else
                	break;
			}
        }
        if ((*ast)->key == routenode)
        {
			if (vt && (*ast)->node.route->next)
            {
                min_print_routenode((*ast)->node.route->rvalue);
                *ast = (*ast)->node.route->next;
                vt = 0;
            }
            else if (!vt)
                *ast = (*ast)->node.route->down;
            else 
            {   
                while ((*ast)->node.route->prev)
                    *ast = (*ast)->node.route->prev;
                if ((*ast)->node.route->up)
                    *ast = (*ast)->node.route->up;
                else
                    break;
            }
		}
	}		
	printf("\n END_AST\n");
}
