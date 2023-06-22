/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_ex_get_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:53:18 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/22 09:46:31 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_len_cmd(t_cmdnode *cmd)
{
	int	len;

	len = 0;
	while (cmd)
	{
		len++;
		cmd = cmd->next;
	}
	return (len);
}

char	**min_ex_get_cmd(t_cmdnode *cmd)
{	
	char	**values;
	int		i;

	i = 0;
	values = (char **)malloc(sizeof(char **) * (ft_len_cmd(cmd) + 1));
	if (values)
	{
		while (cmd)
		{
			values[i++] = cmd->arg;
			cmd = cmd->next;
		}
		values[i] = NULL;
	}
	return (values);
}
