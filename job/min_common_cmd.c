/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_common_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:05:30 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/24 14:58:25 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_get_envp(t_dict *dict)
{
	(void)dict;
		
	return (NULL);
}	


static char **ft_get_paths( t_dict *dict)
{
	int		i;
	char	*temp;
	char 	**paths

	i = 0;
	paths = ft_split((search_key_in_dict(dict, "PATH"))->value,':');	
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
		{
			min_dfree(&paths);
			break;
		}
		gnl_free(paths[i]);
		pi->paths[i++] = temp;
	}
	return (paths);
}


static char	*ft_checkpath(char *cmd, t_dict *dict)
{
	int		i;
	char	**paths;
	char	*path

/* check if cmd is already path*/
	
	i = 0;
	paths = ft_get_paths(dict);
	if (!path)
		return (NULL);
	path = ft_strjoin(paths[i], cmd);
	if (path)
		while (paths[i])
		{	
			if (!access(path, F_OK))
				return (path);
			if (paths[++i])
			{
				free(path);
				path = NULL;
				path = ft_strjoin(paths[i], cmd);
				if (!path)
					break;
			}	t_dict *dict
	}
	return (path);
}

/*   */
int	min_common_cmd(t_jobnode *astjob, t_dict *dict)
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
				path = ft_checkpath(cmd[0], dict)
				if (path)			
					execve(path, cmd, ft_get_envp(dict))
			}
		}
		min_free_job(&job, &path, &cmd);
		return (1);
		}
	}
	waitpid(id, NULL, 0);
	return (0);
}
	






		
			
	
