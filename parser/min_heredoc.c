/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:43:28 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/23 16:34:57 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_find_filename(char *heredoc)
{
	char	*path;
	char	*temp;

	path = ft_strjoin(HEREDOC_PATH, heredoc);
	while (!access(path, F_OK))
	{
		temp = path;
		path = ft_strjoin(path, HERENUM);
		min_free(&temp);
	}
	return (path);
}

static void	ft_heredoc_loop(int fd, char *limiter)
{
	char	*line;

	while (1)
	{
		write(1, HERETXT, ft_strlen(HERETXT));
		line = get_next_line(0);
		if (!line)
		{
			ft_printf_fd(HEREEOF, 2);
			break ;
		}
		if (ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
		{
			min_free(&line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		min_free(&line);
	}
}

int	min_heredoc(t_lexer **token, char *heredoc)
{
	char	*path;
	int		fd;
	char	*limiter;

	path = ft_find_filename(heredoc);
	if (!path)
		return (1);
	limiter = min_here_limiter((*token)->next);
	if (limiter)
	{
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd != -1)
		{
			ft_heredoc_loop(fd, limiter);
			*token = min_here_set_file((*token)->next, path);
			min_free(&limiter);
			if (close(fd))
				return (1);
			return (0);
		}
	}
	ft_printf_fd(HEREFAIL, 2);
	return (1);
}
