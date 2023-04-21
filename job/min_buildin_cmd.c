/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_buildin_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:01:51 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/21 15:43:40 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include ???
static int ft_which_buildin(char *cmd, t_build **build)
{
	int i;
	
	i = 0;
    while (*build && cmd)
    {
        if (ft_strncmp(*build->cmd, cmd, ft_strlen(cmd))
        	break;    
		n++;
        (*build)++;
		
    }
    return (n);
}


static int	ft_run_buildin(char **cmd, t_build **build)
{
		return (*build[ft_wich_buildin(*cmd[0], build)](cmd));
}


/*  */
int	min_buildin(t_jobnode *job, t_dict *dict, t_build **build)
{
    t_expandjob *job;
    char **cmd;
    int error;

	exit = 0;
    job = min_expander(astjob->start, dict, astjob->last);
    if (!job)
        return (1001);
    exit = min_ex_io(job->io);
	if (!exit)
	{
    	cmd = min_get_cmd(job->cmd);
    	if (!cmd)
        	exit = 1001;
	}
	if (!exit)
		exit = ft_run_buildin(cmd, build);		
    min_free_job(&job, NULL , &cmd);
    return (exit);
}

