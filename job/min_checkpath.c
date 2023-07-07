/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_checkpath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:39:19 by lwidmer           #+#    #+#             */
/*   Updated: 2023/07/06 14:27:57 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_get_paths( t_dict *dict)
{
	int		i;
	char	*temp;
	char	**paths;
	t_dict	*path_dict;

	i = 0;
	path_dict = search_key_in_dict(dict, "PATH");
	if (!path_dict)
		return (NULL);
	paths = ft_split(path_dict->value, ':');
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

/*
static int	ft_checkpath_cmd_is_path(char *cmd, char **path)
{
	int		exit;
	int		fd;
	struct	stat file_stat;

	if (!access(cmd, X_OK))
	{
		fd = open(cmd, O_RDONLY);		
		fstat(fd, &file_stat);
		if (S_ISDIR(file_stat.st_mode))
		{
			ft_printf_fd("%s: is a directory\n", 2, cmd);
			*path = ft_strdup("");
			exit = 1;
		} 
		else 
		{
			*path = ft_strdup(cmd);
			exit = 0;
		}
		close (fd);
	}
	else
	{
		*path = ft_strdup("");
		exit = 0;
	}
	return (exit);
}
*/

static int	ft_checkpath_cmd_is_file(char *cmd, char **path)
{
	if (ft_strlen(cmd) <= 1)
	{
		ft_printf_fd("filename argument required\n", 2);
		*path = ft_strdup("");
		return (2);
	}
	if (!access(cmd + 2, F_OK))
	{
		*path = ft_strdup(cmd + 2);
		return (0);
	}
	else
	{
		*path = ft_strdup("");
		return (0);
	}
}

int	ft_build_path_from_dict(char *cmd, char **path, char **paths)
{
	int	i;

	i = 0;
	*path = ft_strjoin(paths[i], cmd);
	if (*path && *cmd)
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
	ft_printf_fd("%s: command not found\n", 2, cmd);
	min_dfree(&paths);
	return (127);
}

int	ft_checkpath(char *cmd, t_dict *dict, char **path)
{
	char	**paths;

	*path = NULL;
	if (cmd[0] == '/')
		return (min_ft_checkpath_cmd_is_path(cmd, path));
	if (cmd[0] == '.')
		return (ft_checkpath_cmd_is_file(cmd, path));
	paths = ft_get_paths(dict);
	if (!*cmd)
	{
		ft_printf_fd("'': command not found\n", 2);
		min_dfree(&paths);
		return (127);
	}
	if (!paths)
	{
		*path = ft_strdup(cmd);
		return (0);
	}
	return (ft_build_path_from_dict(cmd, path, paths));
}
