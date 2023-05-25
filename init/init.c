/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:11:19 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/25 10:56:21 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_terminal(void)
{
	printf("\033[s");
	printf("\033[2J");
	printf("\033[H");
}

int	init_minishell(t_min **min, char **env)
{
	int	status;

	status = 0;
	clear_terminal();
	*min = malloc(sizeof(t_min));
	CHECK_MALLOC(*min, status);
	if (!status)
	{
		ft_bzero(*min, sizeof(t_min));
		(*min)->dict = create_dict_on_startup(env);
		if (!(*min)->dict)
			return (1);
		create_builtin_commands(*min);
		(*min)->builtins = create_builtins((*min)->dict, &(*min)->commands);
		if (!(*min)->builtins)
			return (1);
		(*min)->in = dup(STDIN_FILENO);
		if ((*min)->in == -1)
			return (1);
		(*min)->out = dup(STDOUT_FILENO);
		if ((*min)->out == -1)
			return (1);
	}
	return (0);
}
