/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:23:37 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/29 11:47:39 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_redirect_first(t_pipestruct *pipes)
{
	int	exit;

	exit = 0;
	SET_EXIT_ON_ERROR(close((pipes->pipefd)[0]));
	SET_EXIT_ON_ERROR(close(pipes->dup_out));
	if (!exit)
		SET_EXIT_ON_ERROR(dup2((pipes->pipefd)[1], STDOUT_FILENO));
	SET_EXIT_ON_ERROR(close((pipes->pipefd)[1]));
	if (!exit)
		SET_EXIT_ON_ERROR(dup2(pipes->dup_in, STDIN_FILENO));
	SET_EXIT_ON_ERROR(close(pipes->dup_in));
	return (exit);
}

int	pipe_redirect_middle(t_pipestruct *pipes)
{
	int	exit;

	exit = 0;
	SET_EXIT_ON_ERROR(close((pipes->old_pipefd)[1]));
	SET_EXIT_ON_ERROR(close((pipes->pipefd)[0]));
	SET_EXIT_ON_ERROR(close(pipes->dup_out));
	SET_EXIT_ON_ERROR(close(pipes->dup_in));
	if (!exit)
		SET_EXIT_ON_ERROR(dup2(pipes->pipefd[1], STDOUT_FILENO));
	SET_EXIT_ON_ERROR(close (pipes->pipefd[1]));
	if (!exit)
		SET_EXIT_ON_ERROR(dup2(pipes->old_pipefd[0], STDIN_FILENO));
	SET_EXIT_ON_ERROR(close(pipes->old_pipefd[0]));
	return (exit);
}

int	pipe_redirect_last(t_pipestruct *pipes)
{
	int	exit;

	exit = 0;
	SET_EXIT_ON_ERROR(close((pipes->old_pipefd)[1]));
	SET_EXIT_ON_ERROR(close(pipes->pipefd[0]));
	SET_EXIT_ON_ERROR(close(pipes->pipefd[1]));
	SET_EXIT_ON_ERROR(close(pipes->dup_in));
	if (!exit)
		SET_EXIT_ON_ERROR(dup2(pipes->dup_out, STDOUT_FILENO));
	SET_EXIT_ON_ERROR(close(pipes->dup_out));
	if (!exit)
		SET_EXIT_ON_ERROR(dup2((pipes->old_pipefd)[0], STDIN_FILENO));
	SET_EXIT_ON_ERROR(close(pipes->old_pipefd[0]));
	return (exit);
}
