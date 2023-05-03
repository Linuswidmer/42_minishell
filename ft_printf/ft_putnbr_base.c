/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 09:41:17 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/02 17:40:38 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putnbr_base_fd(long int nbr, char *base, int fd)
{
	int		len;
	char	print;

	len = ft_strlen(base);
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr = nbr * -1;
	}
	if (nbr < len)
	{
		print = base[nbr % len];
		write(fd, &print, 1);
	}
	else
	{
		ft_putnbr_base(nbr / len, base);
		print = base[nbr % len];
		write(fd, &print, 1);
	}
}
