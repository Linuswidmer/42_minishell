/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 09:43:31 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/02 17:41:13 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell"

static unsigned int	parse_int(long int n, char *base, fd)
{
	if (ft_strlen(base) > 10 && n < 0)
	{
		ft_putnbr_base_fd((unsigned int)n, base, fd);
		return (ft_intlen_base((unsigned int)n, ft_strlen(base)));
	}
	else
	{
		ft_putnbr_base_fd(n, base, fd);
		return (ft_intlen_base(n, ft_strlen(base)));
	}
}

static unsigned int	parse_string(char *str, int fd)
{
	if (!str)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	ft_putstr_fd(str, fd);
	return (ft_strlen(str));
}

static unsigned int	parse_pointer(unsigned long long n, int fd)
{
	unsigned int	len;

	if (!n)
	{
		ft_putstr_fd("(nil)", fd);
		return (5);
	}
	len = ft_print_address_hex(n, fd);
	return (len + 2);
}

static unsigned int	parse_ap(const char c, va_list ap, int fd)
{
	if (c == 'd' || c == 'i')
		return (parse_int(va_arg(ap, int), "0123456789"), fd);
	else if (c == 'c')
		ft_putchar_fd(va_arg(ap, int), fd);
	else if (c == '%')
		ft_putchar_fd('%', fd);
	else if (c == 'u')
		return (parse_int(va_arg(ap, unsigned int), "0123456789"), fd);
	else if (c == 's')
		return (parse_string(va_arg(ap, char *), fd));
	else if (c == 'x')
		return (parse_int(va_arg(ap, int), "0123456789abcdef"), fd);
	else if (c == 'X')
		return (parse_int(va_arg(ap, int), "0123456789ABCDEF"), fd);
	else if (c == 'p')
		return (parse_pointer(va_arg(ap, unsigned long long), fd));
	return (1);
}

int	ft_printf_fd(const char *arg, ..., int fd)
{
	va_list	ap;
	int		len;
	int		i;

	if (!arg)
		return (-1);
	i = 0;
	len = 0;
	va_start(ap, arg);
	while (arg[i] != '\0')
	{
		if (arg[i] == '%')
			len = len + parse_ap(arg[++i], ap, fd) - 2;
		else
			ft_putchar_fd(arg[i], fd);
		i++;
	}
	va_end(ap);
	return (len + i);
}
