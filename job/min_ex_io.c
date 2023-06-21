/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_ex_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:24:31 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/21 12:20:27 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*ft_filepath(char *value, char *expath)
{
	char	*filepath;
	char	*path;
	char	*temp;

	if (!value)
		return (NULL);
	if (expath)
		filepath = ft_strjoin(expath, value);
	else if (access(value, F_OK))
		filepath = ft_strdup(value);
	else
	{
		path = getcwd(NULL, 0);
		if (!path)
			return (NULL);
		temp = ft_strjoin(path, "/");
		if (!temp)
		{
			//min_free(path);
			return (NULL);
		}
		filepath = ft_strjoin(temp, value);
		//min_free(temp);
	}
	return (filepath);
}

static int	ft_open_io_out(t_lexertype key, char **filename)
{
	int		fd1;
	int		fd2;
	char	*file;

	file = ft_filepath(*filename, NULL);
	//min_free(filename);
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
		//min_free(file);
		if (fd1 == -1 || fd2 == -1)
		{
		// min_print_error(io->value);
			return (1);
		}
		else
			return (0);
	}
	// min_print_error(io->value);
	return (1);
}

static int	ft_open_io_in(t_lexertype key, char **filename)
{
	int		fd1;
	int		fd2;
	char	*file;

	/*if (min_token_is_io(key)== 2 && evalhere)
		file = min_eval_heredoc(*filename);	
    else*/
	if (min_token_is_io(key) == 2)
		file = *filename;
	else
		file = ft_filepath(*filename, NULL);
//	printf("file is %s\n", file);
	//min_free(filename);
	if (file)
	{
		fd1 = open(file, O_RDONLY);
		if (fd1 != -1)
		{
			fd2 = dup2(fd1, STDIN_FILENO);
			fd2 = close(fd1);
			if (min_token_is_io(key) == 2)
				fd2 = unlink(file);
			//min_free(&file);
			if (fd2 != -1)
				return (0);
		}
	}
	//min_print_error();
	return (1);
}

int	min_ex_io(t_lexertype key, char *filename, char *evalhere)
{
	(void)evalhere;
	if (min_token_is_io(key) > 2)
		return (ft_open_io_out(key, &filename));
	else
		return (ft_open_io_in(key, &filename));
}
