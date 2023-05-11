/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:57:33 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/10 11:10:25 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	min_exit(char **arg)
{
	int	exit;
	int	i;

	i = 0;
	if (!arg[0])
		exit = 256;
	else if (arg[1])
		exit = 2;
	else
	{
		while (arg[0][i] != '\0')
		{
			if (ft_isdigit(arg[0][i]) != 0)
			{
				exit = 2;
				break ;
			}
			i++;
		}
		exit = ft_atoi(arg[0]);
		exit = exit % 256;
		if (exit == 0)
			exit = 256;
	}
	return (exit);
}
