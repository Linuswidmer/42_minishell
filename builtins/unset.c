/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:37:37 by lwidmer           #+#    #+#             */
/*   Updated: 2023/07/05 10:29:32 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_first_dict_entry(t_dict **dict, t_dict *dict_second_entry)
{
	t_dict	*dict_first_entry;

	dict_first_entry = *dict;
	free(dict_first_entry->value);
	free(dict_first_entry->key);
	dict_first_entry->key = dict_second_entry->key;
	dict_first_entry->value = dict_second_entry->value;
	dict_first_entry->next_entry = dict_second_entry->next_entry;
	free(dict_second_entry);
}

static void	unset_not_first_dict_entry(t_dict *var_prev,
				t_dict *var, t_dict *var_next)
{
	while (var_prev->next_entry != var)
		var_prev = var_prev->next_entry;
	min_free(&var->value);
	free(var->key);
	free(var);
	if (var_prev)
		var_prev->next_entry = var_next;
}

int	min_unset(t_dict **dict, char **arg)
{
	t_dict	*var;
	t_dict	*var_prev;
	t_dict	*var_next;
	int		i;

	i = 0;
	while (arg[i])
	{
		var_prev = *dict;
		var = search_key_in_dict(*dict, arg[i]);
		if (var != NULL)
		{
			var_next = var->next_entry;
			if (var == *dict)
				unset_first_dict_entry(dict, var_next);
			else
				unset_not_first_dict_entry(var_prev, var, var_next);
		}
		i++;
	}
	return (1000);
}
