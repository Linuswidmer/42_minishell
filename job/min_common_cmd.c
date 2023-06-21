/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_common_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:05:30 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/21 10:27:16 by lwidmer          ###   ########.fr       */
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
			//min_dfree(&paths);
			break ;
		}
		//min_free(paths[i]);
		paths[i++] = temp;
	}
	return (paths);
}

static int	ft_checkpath_cmd_is_path(char *cmd, t_dict *dict, char **path)
{
	if (!access(cmd, F_OK))
	{
		*path = cmd;
		return (0);
	}
	ft_printf_fd("no such file or direcotry: %s\n", 2, cmd[0]);
	return (1);
}

static int ft_checkpath_cmd_is_file(char *cmd, t_dict *dict, char **path)
{
	int fd;

	if (!access(cmd + 2, F_OK))
	{
		*path = cmd + 2;
		return (0);
	}
	ft_printf_fd("no such file or direcotry: %s\n", 2, cmd[0]);
	return (2);
}

static int	ft_checkpath(char *cmd, t_dict *dict, char **path)
{
	int		i;
	char	**paths;

	/* check if cmd is already path, when starts with "/"*/
	if (cmd[0] == '/')
		return (ft_checkpath_cmd_is_path(cmd, dict, path));
	if (cmd[0] == '.')
		return (ft_checkpath_cmd_is_file(cmd, dict, path));

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
				return (0);
			if (paths[++i])
			{
				//min_free(*path);
				*path = NULL;
				*path = ft_strjoin(paths[i], cmd);
				if (!*path)
					break ;
			}
		}
	}
	ft_printf_fd("command not found: %s",2, cmd[0]);
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
			exit = ft_checkpath(cmd[0], dict, &path);
			exit = execve(path, cmd, ft_get_envp(dict));
			//min_dfree(&cmd);			
			//min_free(&path);
		}
		return (127);
	}
	if (id)
	{
		result = waitpid(id, &status, 0);
		ft_printf_fd("result is %i\n", 2, result);
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
