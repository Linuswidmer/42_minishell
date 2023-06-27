/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_checkpath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:39:19 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/27 11:50:26 by lwidmer          ###   ########.fr       */
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
		*path = ft_strdup(cmd);
		return (0);
	}
	else
	{
		*path = ft_strdup("");
		return (0);
	}
}

static int	ft_checkpath_cmd_is_file(char *cmd, char **path)
{
	if (ft_strlen(cmd) <= 2)
	{
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
	ft_printf_fd("command not found: %s\n", 2, cmd);
	return (1);
}

int	ft_checkpath(char *cmd, t_dict *dict, char **path)
{
	char	**paths;

	if (cmd[0] == '/')
		return (ft_checkpath_cmd_is_path(cmd, path));
	if (cmd[0] == '.')
		return (ft_checkpath_cmd_is_file(cmd, path));
	paths = ft_get_paths(dict);
	if (!path)
		return (1);
	return (ft_build_path_from_dict(cmd, path, paths));
}
