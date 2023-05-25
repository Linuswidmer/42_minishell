/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:08:58 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/25 10:09:09 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_no_dictionary(void)
{
	ft_printf_fd("no dictionary\n", 2);
	return (1002);
}

int	export_not_valid_identifier(char *arg)
{
	ft_printf_fd("export: not a valid identifier %s\n", 2, arg);
	return (1);
}

int	export_check_if_only_digits(char *arg)
{
	int	only_digits_flag;
	int	i;

	i = 0;
	only_digits_flag = 1;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		if (ft_isalpha(arg[i]) != 0 || arg[i] == '_')
			only_digits_flag = 0;
		i++;
	}
	return (only_digits_flag);
}

int	export_check_if_key_is_valid(char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (i == 0 && ft_isdigit(arg[0]) != 0)
		return (1);
	while (arg[i] != '=' && arg[i] != '\0')
	{
		if (ft_isalnum(arg[i]) == 0)
		{
			if (arg[i] == '_' && ft_strlen(arg) > 1)
				i++ ;
			else
				return (1);
		}
		else
			i++;
	}
	if (export_check_if_only_digits(arg))
		return (1);
	else
		return (0);
}
