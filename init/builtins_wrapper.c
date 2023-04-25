/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_wrapper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:35:08 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/25 10:35:17 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

int export_wrapper(t_builtins *builtin, char **args)
{
    return (builtin->commands.min_export(builtin->dict, args));
}

int cd_wrapper(t_builtins *builtin, char **args)
{
	return (builtin->commands.min_cd(builtin->dict, args));
}

int pwd_wrapper(t_builtins *builtin, char **args)
{
	return (builtin->commands.min_pwd(args));
}

int env_wrapper(t_builtins *builtin, char **args)
{
	return (builtin->commands.min_env(builtin->dict, args));
}

int exit_wrapper(t_builtins *builtin, char **args)
{
	return (builtin->commands.min_exit(args));
}

int echo_wrapper(t_builtins *builtin, char **args)
{
	return (builtin->commands.min_echo(args));
}

int unset_wrapper(t_builtins *builtin, char **args)
{
	return (builtin->commands.min_unset(&builtin->dict, args));
}
