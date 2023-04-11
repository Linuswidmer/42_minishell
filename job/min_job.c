/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_job.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:36:54 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/11 17:42:16 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**/
static char *ft_checkpath(t_pipex *pi)
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

pi->cmd = ft_split(pi->argv[2 + i + pi->hd], ' ');
		if (!pi->cmd)
			px_end(ER_ES, 1, 1, pi);
		ft_checkpath(pi);
		if (execve(pi->path, pi->cmd, pi->envp) == -1)
		{
			ft_clpi(pi, i);
			px_end(ER_EE, 1, 1, pi);




int		min_job(t_jobnode **job, t_dict *dict, int fdin)
{
	char *path;
	char **cmd;


	ft_in(job->in, fdin);
	ft_out(job->out);
	min_expander(job, dict);
	
	path = 
	cmd = ft_get_
		
		
	

