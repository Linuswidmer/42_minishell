/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_common_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:05:30 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/27 12:05:27 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/06/21 14:51:28 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/06/02 13:05:38 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/05/11 14:44:29 by jstrotbe         ###   ########.fr       */
/*   Updated: 2023/05/09 13:02:05 by jstrotbe         ###   ########.fr       */
/*   Updated: 2023/05/09 11:33:08 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/05/03 09:46:10 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/05/02 15:24:06 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	child_execute_cmd(t_jobnode *astjob, t_dict *dict)
{
	int		exit;
	char	*path;
	char	**envp;
	char	**cmd;

	cmd = NULL;
	exit = min_io_and_cmd(astjob, dict, &cmd);
	if (!exit)
	{
		envp = (char **)min_get_envp(dict);
		exit = ft_checkpath(cmd[0], dict, &path);
		if (!exit)
		{
			exit = execve(path, cmd, envp);
			perror(cmd[0]);
		}
		min_free(&path);
		min_dfree(&envp);
	}
	min_dfree(&cmd);
	return (127);
}

static int	parent_wait_for_child(pid_t id)
{
	int	exit;
	int	status;
	int	result;

	result = waitpid(id, &status, 0);
	exit = 0;
	if (result == -1)
	{
		result = waitpid(id, &status, 0);
		if (WTERMSIG(status) == 2)
			exit = 1130;
		else if (WTERMSIG(status) == 3)
			exit = 1131;
	}
	else
		exit = WEXITSTATUS(status) + 1000;
	return (exit);
}

int	min_common_cmd(t_jobnode *astjob, t_dict *dict, char f)
{
	int		exit;
	pid_t	id;

	exit = 0;
	if (f)
	{
		id = fork();
		init_signals_cmd();
	}
	else
		id = 0;
	if (!id)
		exit = child_execute_cmd(astjob, dict);
	if (id)
		exit = parent_wait_for_child(id);
	return (exit);
}
