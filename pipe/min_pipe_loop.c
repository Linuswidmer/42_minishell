/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_pipe_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:19:11 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/21 11:59:01 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_loop_close_pipe(int *fd)
{
	int	exit;

	exit = 0;
	close(fd[0]);
	close(fd[1]);
	return (exit);
}

static void	loop_update_pipes(int *old_pipefd, int *pipefd)
{
	old_pipefd[0] = pipefd[0];
	old_pipefd[1] = pipefd[1];
}

static int	pipe_loop_redirection(t_pipestruct *pipes,
		t_pipenode *pipenode, int n)
{
	int	exit;

	if (!n)
		exit = pipe_redirect_first(pipes);
	else if (!pipenode->next)
		exit = pipe_redirect_last(pipes);
	else
		exit = pipe_redirect_middle(pipes);
	return (exit);
}

int	min_pipe_loop(t_pipenode *pipenode, t_dict *dict, t_builtins *builtin,
		t_pipestruct *pipes)
{
	static int	exit;
	int			n;

	n = 0;
	while (pipenode && !exit)
	{
		pipe(pipes->pipefd);
		(pipes->pid)[n] = fork();
		if ((pipes->pid)[n] && n > 0)
			exit = pipe_loop_close_pipe(pipes->old_pipefd);
		if (!((pipes->pid)[n]))
		{
			exit = pipe_loop_redirection(pipes, pipenode, n);
			//ON_SUCCESS(exit, UPDATE_EXIT(exit, min_exit_handler(
			//			min_executer(pipenode->down, dict, builtin, 0))));
			if (!exit)
				exit = min_exit_handler(min_executer(pipenode->down, dict, builtin, 0));	
		}
		ON_SUCCESS(exit, loop_update_pipes(pipes->old_pipefd, pipes->pipefd));
		if (pipenode->next)
			pipenode = pipenode->next->node.pipe;
		else
			pipenode = NULL;
		n++;
	}
	return (exit);
}
