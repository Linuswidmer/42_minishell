/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_common_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:05:30 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/23 17:47:36 by lwidmer          ###   ########.fr       */
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

static char	**ft_get_paths( t_dict *dict)
{
	int		i;
	char	*temp;
	char	**paths;

	i = 0;
	paths = ft_split((search_key_in_dict(dict, "PATH"))->value, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
		{
			min_dfree(&paths);
			break ;
		}
		min_free(&paths[i]);
		paths[i++] = temp;
	}
	return (paths);
}

static int	ft_checkpath_cmd_is_path(char *cmd, char **path)
{
	if (!access(cmd, F_OK))
	{
		*path = cmd;
		return (0);
	}
	ft_printf_fd("no such file or direcotry: %s\n", 2, cmd);
	return (1);
}

static int ft_checkpath_cmd_is_file(char *cmd, char **path)
{
	if (ft_strlen(cmd) <= 2)
		return (2);
	if (!access(cmd + 2, F_OK))
	{
		*path = cmd + 2;
		return (0);
	}
	ft_printf_fd("no such file or direcotry: %s\n", 2, cmd);
	return (2);
}

static int	ft_checkpath(char *cmd, t_dict *dict, char **path)
{
	int		i;
	char	**paths;

	/* check if cmd is already path, when starts with "/"*/
	if (cmd[0] == '/')
		return (ft_checkpath_cmd_is_path(cmd, path));
	if (cmd[0] == '.')
		return (ft_checkpath_cmd_is_file(cmd, path));
	i = 0;
	paths = ft_get_paths(dict);
	if (!path)
		return (1);
	*path = ft_strjoin(paths[i], cmd);
	if (*path)
	{
		while (paths[i])
		{
			if (!access(*path, F_OK))
			{
					min_dfree(&paths);
				return (0);
			}
			if (paths[++i])
			{
				min_free(&(*path));
				*path = ft_strjoin(paths[i], cmd);
				if (!*path)
					break ;
			}
		}
	}
	min_dfree(&paths);	
	ft_printf_fd("command not found: %s\n",2, cmd);
	return (1);
}

int	min_common_cmd(t_jobnode *astjob, t_dict *dict, char f)
{
	char	**cmd;
	char	*path;
	int		exit;
	pid_t	id;
	int		status;
	int		result;
	char	**envp;

	exit = 0;
	if (f)
	{
		id = fork();
		init_signals_cmd();
	}
	else
		id = 0;
	if (!id)
	{
		cmd = NULL;
		exit = min_io_and_cmd(astjob, dict, &cmd);
		if (!exit)
		{	
			envp = (char **)min_get_envp(dict);
			exit = ft_checkpath(cmd[0], dict, &path);
			// hier brauchen wir moch einen guten Weg den exit status zu ueberpruefem
			// wenn exit nicht null ist darf execve nicht ausgefuehrt werden und der path
			// nicht gefreed werden (ausser wir erstellen einen leeren "" Pfad?) die
			// envp muessen aber trotzdem gefreed werden
			//if (exit)
			//	return (exit);
			exit = execve(path, cmd, envp);			
			min_free(&path);
			min_dfree(&envp);
		}
		min_dfree(&cmd);
		return (127);
	}
	if (id)
	{
		result = waitpid(id, &status, 0);
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
	}
	return (exit);
}	
