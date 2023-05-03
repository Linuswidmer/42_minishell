/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:14:00 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/03 15:21:40 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int ft_count_pipeline(t_pipenode *pipe)
{
	int c;

	c = 0;
	while (pipe)
	{
		c++;
		if ( pipe->next)
			pipe = pipe->next->node.pipe;
		else
			pipe = NULL;
	}
	return (c);
}	


int search_pid(pid_t *pid_arr, pid_t return_pid, int arr_len)
{
	int i;

	i = 0;
	while (i < arr_len)
	{
		if (pid_arr[i] == return_pid)
			return (i);
		i++;
	}
	return (i);
}

static int	redirect_child(int in_fd, int out_fd)
{
	dup2(out_fd, STDOUT_FILENO);
    close (out_fd);
    dup2(in_fd, STDIN_FILENO);
    close(in_fd);
	return (0);	
}




int min_pipe(t_pipenode *pipenode, t_dict *dict, t_builtins *build)
{
	int 	lenpipe;
	int 	outfd;
	int		infd;
	pid_t	*pid;
	int		pipefd[2];
	int *old_pipefd;
	int 	n;
	int		exit;
	int		status;

	
	exit = 0;
	n = 0;
	outfd = dup(STDOUT_FILENO);
	infd  = dup(STDIN_FILENO);	
	old_pipefd = malloc(sizeof(int) * 2);
	

	if (outfd == -1 || infd == -1)
	{
		return (1);
	}
	
	lenpipe = ft_count_pipeline(pipenode);
	pid = (pid_t *)malloc(sizeof(pid_t) * lenpipe);
	if (!pid || !old_pipefd)
		return (1);
	while (pipenode && !exit)
	{
		pipe(pipefd);
        pid[n] = fork();
		if (pid[n] && n > 0)
        {   
                close(old_pipefd[0]);
                close(old_pipefd[1]);
        }   
		if (pid[n])
		{
			if (!n)
			{
				close (pipefd[0]);
                close (outfd);
				exit = redirect_child(infd, pipefd[1]);
			}
			if (!pipenode->next)
			{
				close (old_pipefd[1]);
                close (pipefd[0]);
                close (pipefd[1]);
                close(infd);
				exit = redirect_child(old_pipefd[0], outfd);
	  		}
			else
			{
				close (old_pipefd[1]);
                close (pipefd[0]);
                close (outfd);
                close(infd);
				exit = redirect_child(old_pipefd[0], pipefd[1]);		
			}
	
			if (!exit)
				exit = min_exit_handler(min_executer(pipenode->down, dict, build, 0));
				ft_printf_fd("exit: %i", exit);
		}
		if (!exit)
		{				
			old_pipefd[0] = pipefd[0];
        	old_pipefd[1] = pipefd[1];	
		}
		if (pipenode->next)
            pipenode = pipenode->next->node.pipe;
        else
            pipenode = NULL;
		n++;
	}
	if (!exit)
	{
		close(old_pipefd[0]);
    	close(old_pipefd[1]);
    	close (pipefd[0]);
    	close (pipefd[1]);
    	close(outfd);
		 n = 0;
        while ( n < lenpipe)
            {
                pid_t return_pid;
                int pid_pos;

                //write(2, "xxx\n", 5);
                return_pid = waitpid(pid[n], &status, 0);
                if (return_pid == pid[lenpipe - 1] )
                {
                    write(2, "\nxx\n", 5);
                    ft_putnbr_fd(return_pid, 2);
                    write(2,"\n", 2);
                    ft_putnbr_fd(pid[lenpipe - 1], 2);
                    write(2,"\n", 2);
                    if (WEXITSTATUS(status) == 256 )
                        exit = 1000;
                    else
                        exit = WEXITSTATUS(status) + 1000;
                    write(2, "xx\n", 4);
                    ft_putnbr_fd(exit, 2);
                    write(2,"\n", 2);

                }
                n++;
			}

	}
	return (exit);
}
