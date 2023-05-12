/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:25:40 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/12 11:05:05 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict *search_key_in_dict(t_dict *var, char *arg)
{
	while (var)
	{
		if(ft_strncmp(var->key, arg, ft_strlen(arg)) == 0 && ft_strlen(arg) == ft_strlen(var->key))
			return (var);
		else
			var = var->next_entry;
	}
	return (NULL);
}

t_dict *get_dict_last(t_dict *dict)
{
	while (dict->next_entry)
		dict = dict->next_entry;
	return (dict);
}

int write_to_dict(t_dict *var, char *key, char *value)
{
	var->key = ft_strdup(key);
	if (!var->key)
		return (0);
	if (var->value)
		free(var->value);
	if (value)
		var->value = ft_strdup(value);
	return (0);
}

int write_new_entry_to_dict(t_dict *dict, char *new_key, char *new_value)
{
	t_dict *var;
	t_dict *last;

	var = init_env_variable();
	last = get_dict_last(dict);	
	write_to_dict(var, new_key, new_value);
	last->next_entry = var;
	return (0);
}

t_dict *init_env_variable()
{
	t_dict *var;

	var = malloc(sizeof(t_dict));
	if (!var)
		return (NULL);
	var->key = NULL;
	var->value = NULL;
	var->next_entry = NULL;
	return (var);
}

static int update_shlvl_on_startup(t_dict *dict)
{
	int level;
	t_dict *shlvl;
	t_dict *tmp;

	shlvl = search_key_in_dict(dict, "SHLVL");
	if (shlvl)
	{
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
	}
	else
	{
		tmp = get_dict_last(dict);
		tmp->next_entry = init_env_variable();
		if (!tmp->next_entry)
			return (1);
		shlvl = tmp->next_entry;
		write_to_dict(shlvl, "SHLVL", "1");
	}
	return (0);
}

t_dict *create_dict_on_startup(char **env)
{
    t_dict *dict;
    t_dict *var1;
    t_dict *var2;
    char **split_str;
    int i;
	int exit;

    i = 1;
    dict = init_env_variable();
    var1 = dict;
    split_str = ft_split(env[0], '=');
    write_to_dict(var1, split_str[0], split_str[1]);
    free(split_str[0]);
    free(split_str[1]);
    free(split_str[2]);
    free (split_str);
	while (env[i])
    {
        var2 = init_env_variable();
        var1->next_entry = var2;
        var1 = var2; 
        split_str = ft_split(env[i], '=');
        write_to_dict(var1, split_str[0], split_str[1]);
        free(split_str[0]);
        free(split_str[1]);
		free(split_str[2]);
		free(split_str);
        i++;
	}
	exit = update_shlvl_on_startup(dict);
	/*if (exit)
	{
		
	}*/
	return (dict);
}
