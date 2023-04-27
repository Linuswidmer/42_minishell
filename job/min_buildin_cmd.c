/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_buildin_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:01:51 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/27 12:50:30 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int ft_which_buildin(char *cmd, t_build *build)
{
	int i;
	
	i = 0;
    while (build && cmd)
    {
        if (ft_strncmp((*build).name, cmd, ft_strlen(cmd))
        	break;    
	i++;
        build++;
		
    }
    return (i);
}


static int	ft_run_buildin(char **cmd, t_build *build)
{
		int i;
		
		i = ft_wich_buildin(*cmd[0], build);
		return (build[i].func(&build[i], cmd));
}


/*  */
int	min_buildin_cmd(t_jobnode *astjob, t_dict *dict, t_build *build)
{
    char **cmd;
    int exit;

	cmd = NULL;
	exit = min_io_and_cmd(astjob, dict, &cmd);
	if (exit)
		exit = 1001;
	else
		exit = ft_run_buildin(cmd, build);		
   	min_dfree(&cmd);
    return (exit);
}

