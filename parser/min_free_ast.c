/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_free_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:39:31 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/10 15:52:26 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
ft_free_io(t_ionode **io)
{
	t_ionode **temp;
	
	while (*io)
	{
		temp = io;
		*io = (*io)->next;
		free(*temp);
		*temp = NULL; 	
	}
}

ft_free_cmd(t_cmdnode **cmd)
{
	t_cmdnode **temp;

	while (*cmd)
    {
        temp = cmd;
        *cmd = (*cmd)->next;
        free(*temp);
		*temp = NULL;
    }
}


t_ast	*min_free_jobnode(t_ast **ast)
{
	t_ast *up;
	
	up = (*ast)->node.job->up;
	ft_free_io(&((*ast)->node.job->in));	
	ft_free_io(&((*ast)->node.job->out));
	ft_free_cmd(&((*ast)->node.job->cmd));
	free((*ast)->node.job);
	(*ast)->node.job = NULL;
	free(*ast);
	*ast = NULL;
	return (up);
}
*/
void	min_free_ast(t_ast **ast)
{
	(void)ast;
/*	
	char vt;
	
	vt = 0;
	while (*ast)
	{
		if ((*ast)->key == jobnode)
		{
			*ast = min_free_jobnode (ast);
		}
	}*/
}		 	
