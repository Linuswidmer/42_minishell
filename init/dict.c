/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:25:40 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/25 11:40:08 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "libft.h"

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

void write_to_dict(t_dict *var, char *key, char *value)
{
	var->key = ft_strdup(key);
	if (var->value)
		free(var->value);
	var->value = ft_strdup(value);
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

t_dict *create_dict_on_startup(char **env)
{
    t_dict *dict;
    t_dict *var1;
    t_dict *var2;
    char **split_str;
    int i;

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
    /*
    create EXIT_STATUS on startup
    */
  return (dict);
}
