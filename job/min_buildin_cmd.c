/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_buildin_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:01:51 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/21 14:11:24 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

    t_expandjob *job;
    char *path;
    char **cmd;
    int error;

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

