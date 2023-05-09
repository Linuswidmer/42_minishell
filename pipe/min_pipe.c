/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:14:00 by jstrotbe          #+#    #+#             */
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


static int redirect_first_child(t_pipestruct *pipes)
{
	int exit;

	exit = 0;
	SET_EXIT_ON_ERROR(close((pipes->pipefd)[0]));
    SET_EXIT_ON_ERROR(close(pipes->dup_out));
	if (!exit)
		SET_EXIT_ON_ERROR(dup2((pipes->pipefd)[1], STDOUT_FILENO));
    SET_EXIT_ON_ERROR(close((pipes->pipefd)[1]));
	if (!exit)
		SET_EXIT_ON_ERROR(dup2(pipes->dup_in, STDIN_FILENO));
    SET_EXIT_ON_ERROR(close(pipes->dup_in));
	return (exit);	
}

static int redirect_middle_child(int *old_fd, int *fd, int dup_in, int dup_out)
{
	int exit;

	exit = 0;
	SET_EXIT_ON_ERROR(close(old_fd[1]));
    SET_EXIT_ON_ERROR(close(fd[0]));
    SET_EXIT_ON_ERROR(close(dup_out));
    SET_EXIT_ON_ERROR(close(dup_in));
	if (!exit)
		SET_EXIT_ON_ERROR(dup2(fd[1], STDOUT_FILENO));
    SET_EXIT_ON_ERROR(close (fd[1]));
    if (!exit)
		SET_EXIT_ON_ERROR(dup2(old_fd[0], STDIN_FILENO));
    SET_EXIT_ON_ERROR(close(old_fd[0]));
	return (exit);	
	
}


static int redirect_last_child(int *old_fd, int *fd, int dup_in, int dup_out)
{
	int exit;

	exit = 0;
	SET_EXIT_ON_ERROR(close (old_fd[1]));
    SET_EXIT_ON_ERROR(close(fd[0]));
    SET_EXIT_ON_ERROR(close(fd[1]));
    SET_EXIT_ON_ERROR(close(dup_in));
	if (!exit)
		SET_EXIT_ON_ERROR(dup2(dup_out, STDOUT_FILENO));
    SET_EXIT_ON_ERROR(close (dup_out));
    if (!exit)
		SET_EXIT_ON_ERROR(dup2(old_fd[0], STDIN_FILENO));
    SET_EXIT_ON_ERROR(close(old_fd[0]));
	return (0);	

}


int init_pipes(t_pipestruct **pipes, t_pipenode *pipenode)
{
	*pipes = malloc(sizeof(t_pipestruct)) ;

	(*pipes)->dup_out = dup(STDOUT_FILENO);
	(*pipes)->dup_in =  dup(STDIN_FILENO);	
	(*pipes)->old_pipefd = malloc(sizeof(int) * 2);
	(*pipes)->pipefd = malloc(sizeof(int) * 2);
	(*pipes)->lenpipe = ft_count_pipeline(pipenode);
	(*pipes)->pid = malloc(sizeof(pid_t) * (*pipes)->lenpipe);
	//printf("lenpipe is %lu\n", (sizeof(pid_t) * (*pipes)->lenpipe));
	// hier noch exit status setzen
	return (0);
}

int min_pipe(t_pipenode *pipenode, t_dict *dict, t_builtins *build)
{
	t_pipestruct *pipes;
	//int 	lenpipe;
	//pid_t	*pid;
	int 	n;
	int		exit;
	int		status;
	
	exit = 0;
	n = 0;
	exit = init_pipes(&pipes, pipenode);
	//if (!exit)
	//exit = pipe_loop(pipenode, dict, build, pipes);
	
	while (pipenode && !exit)
	{
		pipe(pipes->pipefd);
        (pipes->pid)[n] = fork();
		if ((pipes->pid)[n] && n > 0)
        {   
                close(pipes->old_pipefd[0]);
                close(pipes->old_pipefd[1]);
        }   
		if (!((pipes->pid)[n]))
		{
			if (!n)
				exit = redirect_first_child(pipes);
			else if (!pipenode->next)
				exit = redirect_last_child(pipes->old_pipefd, pipes->pipefd, pipes->dup_in, pipes->dup_out);
			else
				exit = redirect_middle_child(pipes->old_pipefd, pipes->pipefd, pipes->dup_in, pipes->dup_out);
			if (!exit)
				exit = min_exit_handler(min_executer(pipenode->down, dict, build, 0));
				ft_printf_fd("exit: %i", exit);
		}
		if (!exit)
		{				
			(pipes->old_pipefd)[0] = (pipes->pipefd)[0];
        	(pipes->old_pipefd)[1] = (pipes->pipefd)[1];	
		}
		if (pipenode->next)
            pipenode = pipenode->next->node.pipe;
        else
            pipenode = NULL;
		n++;
	}
	
	if (!exit)
	{
		SET_EXIT_ON_ERROR(close((pipes->old_pipefd)[0]));
    	SET_EXIT_ON_ERROR(close((pipes->old_pipefd)[1]));
    	SET_EXIT_ON_ERROR(close((pipes->pipefd)[0]));
    	SET_EXIT_ON_ERROR(close((pipes->pipefd)[1]));
    	SET_EXIT_ON_ERROR(close(pipes->dup_out));
		SET_EXIT_ON_ERROR(close(pipes->dup_in));
		n = 0;
        while ( n < pipes->lenpipe)
            {
                pid_t result;
                int pid_pos;

                result = waitpid(pipes->pid[pipes->lenpipe -1 - n], &status, 0);
				ft_printf_fd("result: %i\n", 2, result);
                if (result == pipes->pid[pipes->lenpipe - 1] )
                {
					ft_printf_fd("last child enters exit status\n", 2);
                    if (WEXITSTATUS(status) == 256 )
                        exit = 1000;
                    else
                        exit = WEXITSTATUS(status) + 1000;
                }
				if (result == -1)
				{
					ft_printf_fd("last child %i enters [-1]\n", 2, pipes->pid[pipes->lenpipe - 1 -n]);
					result = waitpid(pipes->pid[pipes->lenpipe - 1 -n], &status, 0);
					ft_printf_fd("result[-1]: %i\n", 2, result);
					exit = 1130;
				}
                n++;
			}
    }
	return (exit);	
}
