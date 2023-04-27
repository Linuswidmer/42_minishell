/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_common_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:05:30 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/27 14:38:07 by lwidmer          ###   ########.fr       */
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
	char 	**paths;

	i = 0;
	paths = ft_split((search_key_in_dict(dict, "PATH"))->value,':');	
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
		{
			//min_dfree(&paths);
			break;
		}
		//min_free(paths[i]);
		paths[i++] = temp;
	}
	return (paths);
}


static int	ft_checkpath(char *cmd, t_dict *dict, char **path)
{
	int		i;
	char	**paths;

/* check if cmd is already path*/
	
	i = 0;
	paths = ft_get_paths(dict);
	if (!path)
		return (1);
	*path = ft_strjoin(paths[i], cmd);
	if (*path)
		while (paths[i])
		{	
			if (!access(*path, F_OK))
				return (0);
			if (paths[++i])
			{
				//min_free(*path);
				*path = NULL;
				*path = ft_strjoin(paths[i], cmd);
				if (!*path)
					break;
			}
	}
	return (1);
}

int min_common_cmd(t_jobnode *astjob, t_dict *dict)
{
    char	**cmd;
    char	*path;
    int		exit;
    pid_t   id;

    id = fork();
    if (!id)
	{
    	cmd = NULL;
    	exit = min_io_and_cmd(astjob, dict, &cmd);
    	if (!exit)
	{	
			exit = ft_checkpath(cmd[0], dict, &path);
			exit = execve(path, cmd, ft_get_envp(dict));
			//min_dfree(&cmd);			
			//min_free(&path);
	}
	return (1);		
	}
	if (id)						
		waitpid(id, NULL, 0);
    return (0);
}	

	






		
			
	
