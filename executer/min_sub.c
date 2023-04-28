/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:20:46 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/28 19:46:39 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	min_sub(t_ast *ast, t_dict *dict, t_builtins *build)
{
	pid_t	pid;
	int 	fdout;
	int 	status;
	
	write(2, "text", 5);
	pid = fork();
	if (pid == -1)
		return (998);
	if (!pid)
		return (min_exit_handler(min_executer(ast->node.sub->down, dict, build)));
	waitpid(pid, &status, 0);
	return (0);
}	
