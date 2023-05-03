/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_executer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:18:16 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/03 08:52:34 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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


int	min_executer(t_ast *ast, t_dict *dict, t_builtins *build)
{
	if (ast->key == routenode)
	{
		ft_printf_fd("route %i\n",2, 3);
		return (min_route(ast, dict, build));	
	}
	if (ast->key == pipenode)
	{
		ft_printf_fd("pipe\n",2);
	
	  return (ft_pipe_fork(ast, dict, build));
	}	
	if (ast->key == subnode)
	{
		ft_printf_fd("sub\n",2);
    		  return (min_sub(ast, dict, build));
	}
	if (ast->key == jobnode)
	{
		ft_printf_fd("job\n",2);
      		return (min_job(ast, dict, build));
	}

}
