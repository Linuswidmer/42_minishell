/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_exuter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:18:16 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/26 15:47:04 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int ft_pipe_fork(t_ast *ast, t_dict *dict, t_build *build)
{
    pit_t   pipe_pid;
	int     status;
	

	pipe_pis = fork();
    if (pide_pid == -1)
        return (998);
    if (!pide_pid)   
		return (min_pipe(ast->node.pipe, dict, build);
    waitpid(pipe_pid, &status, 0);
	min_set_exit_status(
    return (0);
}
*/

int	min_executer(t_ast *ast, t_dict *dict, t_builtins *build)
{
	/*if (ast->key == routenode)
		return (min_route(ast, dict, build));	
	if (ast->key == pipenode)
	  return (ft_pipe_fork(ast, dict, build));	
	if (ast->key == subnode)
      return (min_sub(ast, dict, build));*/
	if (ast->key == jobnode)
      		return (min_job(ast, dict, build));
      	else
      		return (1001);
}
