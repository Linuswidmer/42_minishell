/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:29:59 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/12 10:00:24 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_dict_env(t_dict *dict)
{
	while (dict)
	{
		if (dict->value)
			printf("%s=%s\n", dict->key, dict->value);
		dict = dict->next_entry;
	}
}

int	min_env(t_dict *dict, char **args)
{
	if (args[0])
	{
		printf("env: too many arguments\n");
		return (1002);
	}
	else
		print_dict_env(dict);
	return (1000);
}
