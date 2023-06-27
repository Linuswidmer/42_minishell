/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_executer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:18:16 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/27 13:49:48 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int ft_pipe_fork(t_ast *ast, t_dict *dict, t_builtins *build)
{
    pid_t   pipe_pid;
	int     status;
	int exit;		

	pipe_pid = fork();
    if (pipe_pid == -1)
        return (998);
    if (!pipe_pid) 
		return (min_exit_handler(min_pipe(ast->node.pipe, dict, build)));
    waitpid(-1, &status, 0);
	 if (WEXITSTATUS(status) == 256 )
        exit = 1000;
    else
        exit = WEXITSTATUS(status) + 1000;	
    
	write(2, "pk\n", 4);
                                        ft_putnbr_fd(exit, 2);
                                        write(2,"\n", 2);
	
	return (exit);
}

*/
int	min_executer(t_ast *ast, t_dict *dict, t_builtins *build, char fork)
{
	if (ast->key == routenode)
	{
		return (min_route(ast, dict, build));
	}
	if (ast->key == pipenode)
	{
		return (min_pipe(ast->u_no.pipe, dict, build));
	}
	if (ast->key == subnode)
	{
		return (min_sub(ast, dict, build));
	}
	if (ast->key == jobnode)
	{
		return (min_job(ast, dict, build, fork));
	}
	return (1);
}
