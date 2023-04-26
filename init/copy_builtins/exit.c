/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:57:33 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/20 13:46:45 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

int min_exit (char **arg)
{
	int status;

	if (!arg[0])
		status = 256;
	else if (arg[2])
		status = 2;
	else
	{
		while (arg[1][i] != '\0')
		{
			if (ft_isdigit(arg[1][i]) != 0)
			{
				status = 2;
				break;
			}
			i++;
		}
		status = ft_atoi(arg);
		status = status % 256;
		if (status == 0)
			status = 256;
  	}
  return (status);
}
