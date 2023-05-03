/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:20:46 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/02 14:11:26 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	min_sub(t_ast *ast, t_dict *dict, t_builtins *build)
{
	pid_t	pid;
	int 	fdout;
	int 	status;
	int		exit;
	
	write(2, "text", 5);
	pid = fork();
	if (pid == -1)
		return (998);
	if (!pid)
		return (min_exit_handler(min_executer(ast->node.sub->down, dict, build)));
	waitpid(-1, &status, 0);
	
	if (WEXITSTATUS(status) == 256 )
        exit = 1000;
    else
        exit = WEXITSTATUS(status) + 1000;

    write(2, "\nsub\n", 6);
    ft_putnbr_fd(exit, 2);
    write(2,"\n", 2);

	return (exit);
}	
