/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_wrapper_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:47:50 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/25 10:42:30 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_wrapper(t_builtins *builtin, char **args)
{
	return (builtin->commands.min_exit(args + 1));
}

int	echo_wrapper(t_builtins *builtin, char **args)
{
	return (builtin->commands.min_echo(args + 1));
}

int	unset_wrapper(t_builtins *builtin, char **args)
{
	return (builtin->commands.min_unset(&(builtin->dict), args + 1));
}
