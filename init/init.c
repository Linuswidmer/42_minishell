/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:11:19 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/26 11:11:29 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void clear_terminal() 
{
  printf("\033[s");
  printf("\033[2J");
  printf("\033[H");
}

int init_minishell(t_min **min, char **env)
{
	clear_terminal();
	
	*min = malloc(sizeof(t_min));
	ft_bzero(*min, sizeof(t_min));
	init_signals();
	// wie machen wir das hier, fragen wir jedes mal status ab?
	(*min)->dict = create_dict_on_startup(env);

	// create builtins here
	create_builtin_commands(*min);	
	(*min)->builtins = create_builtins((*min)->dict, &(*min)->commands);
	(*min)->in = dup(STDIN_FILENO);
	(*min)->out = dup(STDOUT_FILENO);
	return (0);
}
