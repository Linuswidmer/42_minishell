/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_ex_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:52:03 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/24 14:58:13 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "????"

static char *ft_filepath(char *value, char *expath)
{
	char *filepath;
	char *path;
	char *temp;
	
	if (path)
		filepath  = ft_strjoin(expath, value);
	else
	{
		path = getcwd(NULL, 0);
		if (!path)
			return (NULL);
		temp = ft_strjoin(paths, "/");
		if (!temp)
		{
			free(path);
			return (NULL);
		}
		filepath = ft_strjoin(temp, value);
		free(temp);
	}
	return (filepath);
}	


static int	ft_open_io_out(t_ionode *io)
{
    int fd1;
    int fd2;
    char *file;

    file = ft_filepath(io->value, NULL);
	if (file)
	{
		if (min_token_is_io(io->key) == 3)
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (min_token_is_io(io->key) == 4)
			fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd1 != -1)
		{
			fd2 = dup2(fd1, STDOUT_FILENO);
			fd2 = close(fd1);
		}
		free(file);
		if (fd1 == -1 || fd2 == -1)
		{
		min_print_erno(io);
		return (1);
		}
		else
		return (0);
	}
	min_print_erno(io);
	return (1);
}
}



}
static int	ft_open_io_in(t_ionode *io)
{
	int fd1;
	int fd2;
	char *file;
 
	if (min_token_is_io(io->key)== 2)
		file = ft_filepath(io->value, HEREDOC); 
	else
		file = ft_filepath(io->value, NULL);
	if (file)
	{	
    	fd1 = open(file, O_RDONLY);
    	if (fd1 != -1)
    	{
    		fd2 = dup2(fd1, STDIN_FILENO);
        	fd2 = close(fd1);
        	if (min_token_is_io(io->key) == 2)
				fd2 = unlink(file);
			gnl_free(&file);
        	if (fd2 != -1)
            	return (0);
    	}
	}
	min_print_errno();
	return (1);
}


/*difference bewtweem << < is weher the file is stored */


static int	ft_open_io(t_ionode *io)
{

	if(min_token_is_io(io->key) > 2)
	{
		return(ft_open_io_out(io));
	}	
	else
		return (ft_open_io_in(io));
}



int	min_ex_io(t_ionode *io, char buildin)
{
	while (io)
	{
		if (!ft_open_io(io))
			io = io->next;
		else
		{
			if (buildin)
				return(1001);
			else
				return(1);
		}  		
	}
	return (0);
}	
