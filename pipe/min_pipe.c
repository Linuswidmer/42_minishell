/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:14:00 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/25 12:33:09 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "??"


static int ft_count_pipeline(t_pipenode *pipe)
{
	int c;

	c = 0;
	while (pipe)
	{
		c ++;
		pipe = pipe->next;
	}
	return (c);
}	


static int ft_out_reroute(		)


int min_pipe(t_pipenode *pipe, t_dict *dict, t_build **build)
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
		return (-1);
	lenpipe = ft_count_pipeline(pipe);
	pid = (pid_t *)malloc(sizeof(pid_t) * lenpipe);
	
	while (pipe && !exit)
	{
		/* bevor fork*/
		if (pipe->next)
		{


		}
		else
		{


		}		
		pid[n] = fork ();	
		if (!pid[n++])
			exit = min_exit_handler(min_excuter(pipe->down, dict, build));
		if (pipe->next)
		{


		}
		pipe = pipe->next;
	}
	if (!exit)
    {
       n = 0;
      	while ( n < lenpipe)
            {
                waitpid(pid[n]  , &status, 0);
                if ( pid[n] == pid[lenpipe - 1])
                    return( WEXITSTATUS(status));
                n++;
            }
     }
	return (exit);	
}
