/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_ft_checkpath_cmd_is_path.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:57:27 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/07/05 19:11:34 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_if_folder(char *cmd)
{
	int			fd;
	struct stat	file_stat;

	fd = open(cmd, O_RDONLY);
	fstat(fd, &file_stat);
	if (S_ISDIR(file_stat.st_mode))
	{
		ft_printf_fd("%s: is a directory\n", 2, cmd);
		close (fd);
		return (1);
	}
	else
	{
		close (fd);
		return (0);
	}
}

int	min_ft_checkpath_cmd_is_path(char *cmd, char **path)
{
	int		exit;

	if (!access(cmd, X_OK))
	{
		if (check_if_folder(cmd) == 1)
		{
			*path = ft_strdup("");
			exit = 1;
		}
		else 
		{
			*path = ft_strdup(cmd);
			exit = 0;
		}
	}
	else
	{
		*path = ft_strdup("");
		exit = 0;
	}
	return (exit);
}
