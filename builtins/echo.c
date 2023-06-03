/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:21:00 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/23 15:57:28 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_check_arg(char *arg)
{
	int	i;

	if (arg[0] == '-')
	{
		i = 1;
		while (arg[i] != '\0')
		{
			if (arg[i] == 'n')
				i++;
			else
				return (0);
		}
		return (1);
	}
	else
		return (0);
}

int	echo_no_arg(void)
{
	printf("\n");
	return (1000);
}

void	echo_print_args(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
		i++;
	}
}

int	min_echo(char **arg)
{
	int	i;
	int	flag;
	int	n_flag;

	i = 0;
	flag = 1;
	n_flag = 0;
	if (!arg[0])
		return (echo_no_arg());
	while (flag && arg[i])
	{
		flag = echo_check_arg(arg[i]);
		if (!n_flag)
			n_flag = flag;
		i++;
	}
	if (!flag)
		i--;
	echo_print_args(arg + i);
	if (!n_flag)
		printf("\n");
	return (1000);
}
