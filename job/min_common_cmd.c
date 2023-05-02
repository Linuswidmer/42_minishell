/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_common_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:05:30 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/02 09:08:13 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int calc_dict_len(t_dict *dict)
{
	int i;

	i = 0;
	while (dict)
	{
		i++;
		dict = dict->next_entry;
	}
	return(i);
}

char	*const* ft_get_envp(t_dict *dict)
{
	int i;
	int dict_len;
	char **envp;
	int entry_len;

	i = 0;
	dict_len = calc_dict_len(dict);
	envp = malloc(sizeof(char *) * dict_len + 1);
	while (i < dict_len)
	{
		entry_len = ft_strlen(dict->key) + ft_strlen(dict->value) + 2;
		envp[i] = malloc(sizeof(const char) * entry_len);
		ft_bzero(envp[i], entry_len);
		ft_strlcat(envp[i], dict->key, entry_len);
		ft_strlcat(envp[i], "=", entry_len);
		ft_strlcat(envp[i], dict->value, entry_len);
		dict = dict->next_entry;
		i++;
	}
	envp[i] = NULL;
	return (envp);
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
	int status;

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
		waitpid(id, &status, 0);
	exit = WEXITSTATUS(status) + 3000;
	ft_putnbr_fd(exit, 2);
    return (exit);
}	



		
			
	
