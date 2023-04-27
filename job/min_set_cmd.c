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

#include "minishell.h"

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


static int ft_set_cmd(char *arg, t_cmdnode **cmd)
{
	t_cmdnode    *end;

    if (!*cmd)
        {
            *cmd = ft_init_cmd(arg);
            end = *cmd;
        }
    else
        {
            end = ft_last_cmdnode(*cmd);
            end->next= ft_init_cmd(arg);
            end = end->next;
        }
    if(!end)
        return (1);
    else
    	return (0);    	
}


int	min_set_cmd(t_lexer **token, t_dict *dict, t_cmdnode **cmd)
{
	char **values;
	int	exit;
	int	i;
		
	i = 0;
	values = min_word_eval(token, dict);
	printf("%s\n", values[0]);
	if (!values)
		return (1);
	else
	{
		exit = 0;
		while (*values && !exit)
		{
			exit = ft_set_cmd(*values++, cmd);
		}
	}
	return (exit);
}
		









