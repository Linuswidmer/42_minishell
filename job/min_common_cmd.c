/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_common_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:05:30 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/24 12:47:26 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "???"
static void	ft_init_path(t_pipex *pi, char *envp[])
{
	int		i;
	char	*temp;

	i = 0;
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			pi->paths = ft_split(((*envp) + 5), ':');
		envp++;
	}
	if (!pi->paths)
		px_end(ER_SPL, 1, 1, pi);
	while (pi->paths[i])
	{
		temp = ft_strjoin(pi->paths[i], "/");
		if (!temp)
			px_end(ER_JOI, 1, 1, pi);
		gnl_free(&pi->paths[i]);
		pi->paths[i++] = temp;
	}
}


static int	ft_checkpath(t_pipex *pi)
{
	int	i;

	i = 0;
	pi->path = ft_strjoin(pi->paths[i], pi->cmd[0]);
	if (!pi->path)
		px_end(ER_PMA, 1, 1, pi);
	while (pi->paths[i])
	{	
		if (!access(pi->path, F_OK))
			return (1);
		if (pi->paths[++i])
		{
			free(pi->path);
			pi->path = NULL;
			pi->path = ft_strjoin(pi->paths[i], pi->cmd[0]);
			if (!pi->path)
				px_end(ER_PJOI, 1, 1, pi);
		}
	}
	return (0);
}

/*   */
int	min_common_cmd(t_jobnode *job, t_dict *dict)
{
	t_expandjob *job;
    char **cmd;
	char *path;
    int exit;
	pid_t	id;

	id = fork();
	if (!id)
	{	
		cmd = NULL;
		path = NULL;
    	exit = 0;
    	job = min_expander(astjob->start, dict, astjob->last);
    	if (!job)
        	return (1);
		if (!min_ex_io(job->io, 1))
 		{	   	
 			cmd = min_ex_get_cmd(job->cmd);
    		if (cmd)
			{
				path= ft_checkpath(pi)
				if (path)			
					execve(pi->path, pi->cmd, pi->envp)
			}
		}
		min_free_job(&job, &path, &cmd);
		return (1);
		}
	}
	waitpid(-1, NULL, 0);
	return (0);
}
	






		
			
	
