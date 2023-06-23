/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:37:37 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/23 15:16:43 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unset_first_dict_entry(t_dict **dict, t_dict *dict_second_entry)
{
	t_dict	*dict_first_entry;

	dict_first_entry = *dict;
	free(dict_first_entry->value);
	dict_first_entry->key = dict_second_entry->key;
	dict_first_entry->value = dict_second_entry->value;
	dict_first_entry->next_entry = dict_second_entry->next_entry;
	free(dict_second_entry);
	return (1000);
}

int	min_unset(t_dict **dict, char **arg)
{
	t_dict	*var;
	t_dict	*var_prev;
	t_dict	*var_next;

	var_prev = *dict;
	var = search_key_in_dict(*dict, arg[0]);
	if (var)
		var_next = var->next_entry;
	if (var == NULL)
		return (1000);
	else if (var == *dict)
		return (unset_first_dict_entry(dict, var_next));
	else
	{
		while (var_prev->next_entry != var)
			var_prev = var_prev->next_entry;
	}
	free(var->value);
	free(var->key);
	free(var);
	if (var_prev)
		var_prev->next_entry = var_next;
	return (1000);
}
