/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:57:33 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/25 10:16:38 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"
#include "libft.h"

int min_exit (char **arg)
{
	int status;
	int i;


	i = 0;
	if (!arg[0])
		status = 256;
	else if (arg[1])
		status = 2;
	else
	{
		while (arg[0][i] != '\0')
		{
			if (ft_isdigit(arg[0][i]) != 0)
			{
				status = 2;
				break;
			}
			i++;
		}
		status = ft_atoi(arg[0]);
		status = status % 256;
		if (status == 0)
			status = 256;
  	}
  return (status);
}
