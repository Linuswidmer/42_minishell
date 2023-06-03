/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:04:56 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/29 13:05:08 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_shlvl_entry_found(t_dict *shlvl)
{
	int	level;

	if (shlvl->value)
	{
		level = ft_atoi(shlvl->value);
		free(shlvl->value);
	}
	else
		level = 0;
	shlvl->value = ft_itoa(level + 1);
	if (!shlvl->value)
		return (1);
	else
		return (0);
}

static int	update_shlvl_entry_not_found(t_dict *dict)
{
	t_dict	*tmp;

	tmp = get_dict_last(dict);
	tmp->next_entry = init_env_variable();
	if (!tmp->next_entry)
		return (1);
	write_to_dict(tmp->next_entry, "SHLVL", "1");
	return (0);
}

int	min_update_shlvl_on_startup(t_dict *dict)
{
	int		exit;
	t_dict	*shlvl;

	shlvl = search_key_in_dict(dict, "SHLVL");
	if (shlvl)
		exit = update_shlvl_entry_found(shlvl);
	else
		exit = update_shlvl_entry_not_found(dict);
	return (exit);
}
