/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:20:46 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/27 13:38:37 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	ft_store_old_fd(int *infd, int *outfd)
{
	*outfd = dup(STDOUT_FILENO);
	*infd = dup(STDIN_FILENO);
}

static int	ft_fd(int infd, int outfd, int exit)
{
	dup2(outfd, STDOUT_FILENO);
	dup2(infd, STDIN_FILENO);
	close(outfd);
	close(infd);
	return (exit);
}

int	min_sub(t_ast *ast, t_dict *dict, t_builtins *build)
{
	pid_t	pid;
	int		status;
	int		exit;
	int		infd;
	int		outfd;

	ft_store_old_fd(&infd, &outfd);
	exit = min_expander(ast->u_no.sub->start, dict, ast->u_no.sub->last, NULL);
	if (!exit)
	{
		pid = fork();
		if (pid == -1)
			return (998);
		if (!pid)
			return (ft_fd(infd, outfd, min_exit_handler(min_executer
						(ast->u_no.sub->down, dict, build, 0))));
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 256)
			exit = 1000;
		else
			exit = WEXITSTATUS(status) + 1000;
	}
	else
		exit += 1000;
	return (ft_fd(infd, outfd, exit));
}
