/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_dict_builtins_min.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:26:19 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/23 17:20:19 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_dict(t_dict *dict)
{
	t_dict	*tmp;

	while (dict)
	{
		if (dict->key)
			free(dict->key);
		if (dict->value)
			free(dict->value);
		tmp = dict->next_entry;
		free(dict);
		dict = tmp;
	}
	return (0);
}

int	free_builtins(t_builtins *builtins)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		free((char *)(builtins[i].name));
		i++;
	}
	free (builtins);
	return (0);
}

int	free_min(t_min *min)
{
	free(min);
	return (0);
}
