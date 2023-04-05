/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_set_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:24:24 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/05 18:08:41 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"





static t_cmdnode *ft_init_cmdnode(t_lexer *token, t_ast *ast)	 
{
	t_cmdnode *node;

	node = (t_cmdnode *)malloc(sizeof(t_cmdnode));
	if (!node)
		return (node);
	ft_bzero(node, sizeof(t_cmdnode));	
	node->arg = token->value;
	return (node);
}


/* job-cmd && end can be NULL*/

void	min_set_cmd(t_lexer *token, t_ast *ast)
{
	    t_jobnode *job;
	t_cmdnode *end;

	job = ast->node.job;
	if (!job->cmd)
		job->cmd = ft_init_cmdnode(token, ast);
	else
	{
		end = min_last_cmdnode(job->cmd);
		end = ft_init_cmdnode(token, ast);
	}
}	
