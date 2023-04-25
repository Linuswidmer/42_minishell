/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_set_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:22:37 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/17 14:17:18 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static t_cmdnode *ft_init_cmd(char *arg)
{
    t_cmdnode *cmd;

    cmd = (t_cmdnode *)malloc(sizeof(t_cmdnode));
    if (!cmd)
        return (NULL);
    ft_bzero(cmd, sizeof(t_cmdnode));
	cmd->arg = arg;
    return (cmd);
}

static t_cmdnode *ft_last_cmdnode(t_cmdnode *node)
{
        while (node->next)
                node = node->next;
    return (node);
}


static void	ft_set_cmd(char *arg, t_expandjob **job)
{
	t_cmdnode    *end;

    if (!(*job)->cmd)
        {
            job->cmd = ft_init_cmd(arg);
            end = job->cmd;
        }
    else
        {
            end = ft_last_cmdnode(job->cmd);
            end->next= ft_init_cmd(arg);
            end = end->next;
        }
    if(!end)
        min_expander_malloc_fail(job);
}


t_lexer *min_set_cmd(t_lexer *token, t_expandjob **job, t_dict *dict)
{
	char **values;

	values = min_word_eval(&token, dict);
	if (!values)
		min_expander_malloc_fail(job);
	else
	{
		while (*values && job)
			ft_set_cmd(*(*values)++, job);
	}
	return (token)
}
		









