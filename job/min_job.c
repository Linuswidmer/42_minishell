/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_job.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:36:54 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/17 14:25:08 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "expander.h"


static ft_in()

static ft_out()

static ft_get_cmd()

static ft_get_path()

static ft_free_job()


int		min_job(t_jobnode *astjob, t_dict *dict, int fdin)
{
	t_expandjob	*job;
	char *path;
	char **cmd;
	

	job = min_expander(astjob->start, dict, astjob->last);
	if (!job)
		return (1);
	if(ft_in(job->in, fdin))
		return (1);
	if(ft_out(job->out))
		return (1);
	cmd = ft_get_cmd(job->cmd);
	if (!cmd)
		return (1);
	if (min_buildin(cmd[0]))
	{
		path = ft_get_path (cmd[0], dict);
		if (!path)
			return (1);
		global = 0;
		global = execve(path, cmd, pi->envp);
	}
	ft_free_job(job, path ,cmd);
	return (0);	
}
	
		
	

