/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address_hex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 09:36:32 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/02 17:39:26 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minshell.h"

static void	print_address(unsigned long long address, int fd)
{
	char	print;
	char	*base;

	base = ft_strdup("0123456789abcdef");
	if (address < 16)
	{
		print = base[address % 16];
		write(fd, &print, 1);
	}
	else
	{
		print_address(address / 16);
		print = base[address % 16];
		write(fd, &print, 1);
	}
}

static unsigned int	length_address(unsigned long long address)
{
	unsigned int	len;

	len = 1;
	while (address > 15)
	{
		len++;
		address = address / 16;
	}
	return (len);
}

unsigned int	ft_print_address_hex(unsigned long long address, int fd)
{
	if (address)
	{
		ft_putstr_fd("0x", fd);
		print_address(address, fd);
	}
	return (length_address(address));
}
