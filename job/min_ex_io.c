/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_ex_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:52:03 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/24 11:44:25 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "????"

static int	ft_open_io_out()
{


}
static int	ft_open_io_in()
{
	




}

static int	ft_open_io(t_ionode *io)
{
	int fd1;
	int fd2;
	
	fd2 = 0;
	
	if(min_token_is_io(io->key) < 3)
	{
		fd1 = open(io->value, O_RDONLY);
		if (fd1 != -1)
		{
			fd2 = dup2(fd1, STDIN_FILENO);
		 	fd2 = close(fd1);
			if (min_token_is_io(io->key) == 2)
				fd2 = unlink(io->value);
		}
		if (fd1 == -1 || fd2 == -1)
		{
			min_print_erno(io);
			return (1);	
		}
		else 
			return (0);
	}
	if(min_token_is_io(io->key) > 2)
	{
		if (min_token_is_io(io->key) == 3)
			fd = open(io->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (min_token_is_io(io->key) == 4)
			fd = open(io->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd1 != -1)
		{
			fd2 = dup2(fd1, STDOUT_FILENO);
            fd2 = close(fd1);
		}
		if (fd1 == -1 || fd2 == -1)
        {
            min_print_erno(io);
            return (1);
        }
        else
            return (0);
	}	
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
