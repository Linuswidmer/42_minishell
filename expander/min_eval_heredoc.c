/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_eval_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:01:44 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/08 09:54:35 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int *ft_find next(char *old, char **temp)
{
	min_free(temp);
	*temp = ft_strchr(old, '$'); 
	return (0);

}	


static	char *ft_eval_line(char **old, int fd1)
{
	char *new;
	int c;
	char *temp;

	temp = old;
	c = 0;
	
	while (temp)
	{
		while (temp && temp++ != '$')
			 c++;
	}	
	return (new);
}	
		









char *min_eval_heredoc(char *oldfile)
{
	char *newfile;
	int fd1;
	int fd2;
	char *line;

	newfile = ft_strjoin(oldfile, HEREDOC_EVAL);
	if (newfile)
	{
		fd1 = open(newfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		fd2 = open(oldfile, O_RDONLY);
		if (fd1 != -1 && fd2 != -1)
		{	
			line =  get_next_line(fd2);
			while (line)
			{
				line = 	ft_eval_line(&line, fd1);
				if (!line) 
					break;
				min_free(line);
				line = get_next_line(fd2);
			}
			fd1 = close(fd1);
			fd2 = close(fd2); 	
		}
	}
	if (fd1 < 0 || fd2 < 0)
		min_free(newfile);
	unlink(oldfile); 	
	return (newfile)
