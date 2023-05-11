/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_common_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:05:30 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/11 10:07:15 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/05/09 13:02:05 by jstrotbe         ###   ########.fr       */
/*   Updated: 2023/05/09 11:33:08 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/05/03 09:46:10 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/05/02 15:24:06 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!access(cmd, F_OK))
	{
		*path = cmd;
		return (0);	
	}
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



int min_common_cmd(t_jobnode *astjob, t_dict *dict, char f)
{
    char	**cmd;
    char	*path;
    int		exit;
    pid_t   id;
	int status;
	int result;
	//struct sigaction sa_sigint_job;

	if (f)
	{
    	id = fork();
		init_signals_cmd();
	}
	else
		id = 0;
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
			return (127);		
	}
	if (id)
	{
		result = waitpid(id, &status, 0);
		ft_printf_fd("result is %i\n",2, result);
		if (result == -1)
		{
			//kill(id, SIGINT);
			result = waitpid(id, &status, 0);
			init_signals();
			if (WTERMSIG(status) == 2)
				exit = 1130;
			else if (WTERMSIG(status) == 3)
				exit = 1131;
		}
		else
			exit = WEXITSTATUS(status) + 1000;
	}
    return (exit);
}	



		
			
	
