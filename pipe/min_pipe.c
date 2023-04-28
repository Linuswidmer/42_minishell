/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:14:00 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/28 20:55:21 by lwidmer          ###   ########.fr       */
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

int min_pipe(t_pipenode *pipenode, t_dict *dict, t_builtins *build)
{
	int 	lenpipe;
	int 	outfd;
	pid_t	*pid;
	int		pipefd[2];
	int 	n;
	int		exit;
	int		status;

	
	exit = 0;
	n = 0;
	outfd = dup(STDOUT_FILENO);
	if (outfd == -1)
	{
		return (1);

	}
	lenpipe = ft_count_pipeline(pipenode);
	pid = (pid_t *)malloc(sizeof(pid_t) * lenpipe);
	while (pipenode && !exit)
	{
		/* bevor fork*/
		/* create and route to pipe */
		if (pipenode->next)
		{
			if (pipe(pipefd) == -1)
            	return (1);
        	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
            	return (1);
        	if (close(pipefd[1]) == -1)
            	return (1);
		}
		/* last pipe route to STDOUT_FILENO */	
		else
		{
			if (dup2(outfd, STDOUT_FILENO) == -1)
                return (1);
			close(outfd);
		}		
		pid[n] = fork ();	
		if (!pid[n++])
		{
			exit = min_exit_handler(min_executer(pipenode->down, dict, build));
			close(pipefd[0]);
		}	
		if (!exit && pipenode->next)
		{
			if (dup2(pipefd[0], STDIN_FILENO) == -1)
            	return (1);
        	if (close(pipefd[0]) == -1)
            	return (1);
		}
		if (pipenode->next)
			pipenode = pipenode->next->node.pipe;
		else
			pipenode = NULL;
	}
	if (!exit)
    {
       n = 0;
      	while ( n < lenpipe)
            {
				pid_t return_pid;
				int pid_pos;

				//write(2, "xxx\n", 6);
                return_pid = waitpid(-1, &status, 0);
				if (return_pid == pid[lenpipe -1])
				{
					if (WEXITSTATUS(status) < 3000)
						exit = WEXITSTATUS(status) + 3000;
					else
						exit = WEXITSTATUS(status);	
					ft_putnbr_fd(exit, 2);
				}
				//write(2, "xxx\n", 6);
                //if ( pid[n] == pid[lenpipe - 1])
				//	g_status =  WEXITSTATUS(status);	
                  //  return( WEXITSTATUS(status));
				pid_pos = search_pid(pid, return_pid, lenpipe);
				if (pid_pos - 1 >= 0)
				{
					write(2, "kill\n", 6);
					kill(pid[pid_pos - 1], SIGPIPE);
				}
				n++;
            }
     }
	return (exit);	
}
