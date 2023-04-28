/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_executer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:18:16 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/28 20:17:27 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int ft_pipe_fork(t_ast *ast, t_dict *dict, t_builtins *build)
{
    pid_t   pipe_pid;
	int     status;
	

	pipe_pid = fork();
    if (pipe_pid == -1)
        return (998);
    if (!pipe_pid) 
		return (min_exit_handler(min_pipe(ast->node.pipe, dict, build)));
    waitpid(pipe_pid, &status, 0);
    return (WEXITSTATUS(status));
}


int	min_executer(t_ast *ast, t_dict *dict, t_builtins *build)
{
	if (ast->key == routenode)
		return (min_route(ast, dict, build));	
	if (ast->key == pipenode)
	{
		write(2, "pipe\n", 5);
	  return (ft_pipe_fork(ast, dict, build));
	}	
	if (ast->key == subnode)
    		  return (min_sub(ast, dict, build));
	if (ast->key == jobnode)
	{		write(2, "job\n", 4);
      		return (min_job(ast, dict, build));
	}
      	else
     	 return (1001);
}
