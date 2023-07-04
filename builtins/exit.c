/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:57:33 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/28 13:39:32 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_check_if_numeric(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0)
		{
			if (!(i == 0 && (arg[0] == '+' || arg[0] == '-')))
				return (1);
		}
		i++;
	}
	return (0);
}

static int	exit_too_many_args(void)
{
	ft_printf_fd("exit: too many arguments\n", 2);
	return (1002);
}

int	min_exit(char **arg)
{
	int	exit;
	int	i;

	i = 0;
	ft_printf_fd("exit\n", 2);
	if (!arg[0])
		exit = 256;
	else if (arg[1])
		return (exit_too_many_args());
	else
	{
		if (exit_check_if_numeric(arg[0]))
		{
			ft_printf_fd("exit: %s: numeric argument required\n", 2, arg[0]);
			return (2);
		}
		exit = ft_atoi(arg[0]);
		exit = exit % 256;
		if (exit == 0)
			exit = 256;
	}
	return (exit);
}
