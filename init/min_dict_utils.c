/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_dict_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:06:56 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/23 17:23:09 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*search_key_in_dict(t_dict *var, char *arg)
{
	while (var)
	{
		if (ft_strncmp(var->key, arg, ft_strlen(arg)) == 0
			&& ft_strlen(arg) == ft_strlen(var->key))
		{
			return (var);
		}
		else
			var = var->next_entry;
	}
	return (NULL);
}

t_dict	*get_dict_last(t_dict *dict)
{
	while (dict->next_entry)
		dict = dict->next_entry;
	return (dict);
}

int	write_to_dict(t_dict *var, char *key, char *value)
{
	var->key = ft_strdup(key);
	if (!var->key)
		return (0);
	if (var->value)
		free(var->value);
	if (value)
		var->value = ft_strdup(value);
	else
		var->value = NULL;
	return (0);
}

int	write_new_entry_to_dict(t_dict *dict, char *new_key, char *new_value)
{
	t_dict	*var;
	t_dict	*last;

	var = init_env_variable();
	last = get_dict_last(dict);
	write_to_dict(var, new_key, new_value);
	last->next_entry = var;
	return (0);
}

t_dict	*init_env_variable(void)
{
	t_dict	*var;

	var = malloc(sizeof(t_dict));
	if (!var)
		return (NULL);
	var->key = NULL;
	var->value = NULL;
	var->next_entry = NULL;
	return (var);
}
