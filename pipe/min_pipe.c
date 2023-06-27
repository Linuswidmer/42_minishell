/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:28:08 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/22 14:11:39 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_pipeline(t_pipenode *pipe)
{
	int	c;

	c = 0;
	while (pipe)
	{
		c++;
		if (pipe->next)
			pipe = pipe->next->u_no.pipe;
		else
			pipe = NULL;
	}
	return (c);
}	

int	search_pid(pid_t *pid_arr, pid_t return_pid, int arr_len)
{
	int	i;

	i = 0;
	while (i < arr_len)
	{
		if (pid_arr[i] == return_pid)
			return (i);
		i++;
	}
	return (i);
}

int	init_pipes(t_pipestruct **p_pipes, t_pipenode *pipenode)
{
	t_pipestruct	*pipes;

	pipes = malloc(sizeof(t_pipestruct));
	if (!pipes)
		return (1);
	pipes->dup_out = dup(STDOUT_FILENO);
	pipes->dup_in = dup(STDIN_FILENO);
	pipes->old_pipefd = malloc(sizeof(int) * 2);
	if (!pipes->old_pipefd)
		return (1);
	pipes->pipefd = malloc(sizeof(int) * 2);
	if (!pipes->pipefd)
		return (1);
	pipes->lenpipe = ft_count_pipeline(pipenode);
	pipes->pid = malloc(sizeof(pid_t) * pipes->lenpipe);
	if (!pipes->pid)
		return (1);
	*p_pipes = pipes;
	return (0);
}

int	parent_wait_for_children(t_pipestruct *pipes)
{
	int	n;
	int	status;
	int	exit;
	int	result;

	n = 0;
	while (n < pipes->lenpipe)
	{
		result = waitpid(pipes->pid[pipes->lenpipe -1 - n], &status, 0);
		if (result == pipes->pid[pipes->lenpipe - 1])
		{
			if (WEXITSTATUS(status) == 256)
				exit = 1000;
			else
				exit = WEXITSTATUS(status) + 1000;
		}
		if (result == -1)
		{
			result = waitpid(pipes->pid[pipes->lenpipe - 1 - n], &status, 0);
			exit = 1130;
		}
		n++;
	}
	return (exit);
}

int	min_pipe(t_pipenode *pipenode, t_dict *dict, t_builtins *build)
{
	t_pipestruct	*pipes;
	int				n;
	int				exit;

	exit = 0;
	n = 0;
	exit = init_pipes(&pipes, pipenode);
	exit = min_pipe_loop(pipenode, dict, build, pipes);
	if (!exit)
	{
		SET_EXIT_ON_ERROR(close((pipes->old_pipefd)[0]));
		SET_EXIT_ON_ERROR(close((pipes->old_pipefd)[1]));
		SET_EXIT_ON_ERROR(close((pipes->pipefd)[0]));
		SET_EXIT_ON_ERROR(close((pipes->pipefd)[1]));
		SET_EXIT_ON_ERROR(close(pipes->dup_out));
		SET_EXIT_ON_ERROR(close(pipes->dup_in));
		exit = parent_wait_for_children(pipes);
	}
	free_pipestruct(pipes);
	return (exit);
}
