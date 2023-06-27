/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_ex_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:24:31 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/27 11:25:40 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*ft_filepath(char *value)
{
	char	*filepath;
	char	*path;
	char	*temp;

	if (!value)
		return (NULL);
	else if (value[0] == '.' || value[0] == '/')
	{
		filepath = ft_strdup(value);
		min_free(&value);
	}
	else
	{
		path = getcwd(NULL, 0);
		if (!path)
			return (NULL);
		temp = ft_strjoin(path, "/");
		min_free(&path);
		if (!temp)
			return (NULL);
		filepath = ft_strjoin(temp, value);
		min_free(&temp);
	}
	return (filepath);
}

static int	ft_open_io_out(t_lexertype key, char **filename)
{
	int		fd1;
	int		fd2;
	char	*file;

	file = ft_filepath(*filename);
	min_free(filename);
	if (file)
	{
		if (min_token_is_io(key) == 3)
			fd1 = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (min_token_is_io(key) == 4)
			fd1 = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd1 != -1)
		{
			fd2 = dup2(fd1, STDOUT_FILENO);
			fd2 = close(fd1);
		}
		min_free(&file);
		if (fd1 == -1 || fd2 == -1)
			return (1);
		else
			return (0);
	}
	return (1);
}

static int	ft_norm(char **filename, char **file, char print)
{
	if (filename)
	{
		*file = ft_filepath(*filename);
		min_free(filename);
		return (0);
	}
	if (print)
	{
		ft_printf_fd("%s: ", 2, *file);
		perror(""); 
		min_free(file);
		return (1);
	}
	min_free(file);
	return (0);
}

static int	ft_open_io_in(t_lexertype key, char **filename)
{
	int		fd1;
	int		fd2;
	char	*file;

	if (min_token_is_io(key) == 2)
		file = *filename;
	else
		ft_norm(filename, &file, 0);
	if (file)
	{
		fd1 = open(file, O_RDONLY);
		if (fd1 != -1)
		{
			fd2 = dup2(fd1, STDIN_FILENO);
			fd2 = close(fd1);
			if (min_token_is_io(key) == 2)
				fd2 = unlink(file);
			if (fd2 != -1)
				return (ft_norm(NULL, &file, 0));
		}
	}
	return (ft_norm(NULL, &file, 1));
}

int	min_ex_io(t_lexertype key, char *filename, char *evalhere)
{
	(void)evalhere;
	if (min_token_is_io(key) > 2)
		return (ft_open_io_out(key, &filename));
	else
		return (ft_open_io_in(key, &filename));
}
