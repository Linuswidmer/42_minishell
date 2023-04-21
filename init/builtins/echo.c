/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:21:00 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/20 12:27:54 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../init.h"

int echo_check_arg(char *arg)
{
	int i;

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

int min_echo (char **arg)
{
	int i;
	int n_flag;

	i = 0;
	n_flag = echo_check_arg(arg[0])
	if (n_flag)
	{
		i++;
		while (arg[i])
		{
			printf("%s", arg[i])
			i++;
		}
	}
	else
	{
		while (arg[i])
		{
			printf("%s\n", arg[i])
			i++;
		}
	}
}
