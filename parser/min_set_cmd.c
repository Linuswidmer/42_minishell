/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_set_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:24:24 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/17 14:20:11 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"





static t_cmdnode *ft_init_cmdnode(t_lexer *token)	 
{
	t_cmdnode *cmd;

	cmd = (t_cmdnode *)malloc(sizeof(t_cmdnode));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_cmdnode));	
	cmd->value = token->key;
	cmd->arg = token->value;
	return (cmd);
}


void	min_set_cmd(t_lexer *token, t_ast **ast)
{
	t_jobnode *job;
	t_cmdnode *end;

	job = (*ast)->node.job;
	if (!job->cmd)
	{
		job->cmd = ft_init_cmdnode(token);
		if (!job->cmd)
			min_parser_malloc_fail(ast);
	}
	else
	{
		end = min_last_cmdnode(job->cmd);
		end->next = ft_init_cmdnode(token);
		if (!end->next)
			min_parser_malloc_fail(ast);
	}
}	
