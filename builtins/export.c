/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:18:08 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/12 10:32:50 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "builtins.h"

void write_to_env_variable(t_dict *var, char *key, char *value)
{
	var->key = ft_strdup(key);
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

void create_dict_on_startup(t_dict *var1, char **env)
{
	t_dict *var2;
	char **split_str;
	int	i;

	i = 1;
	split_str = ft_split(env[0], '=');
	write_to_env_variable(var1, split_str[0], split_str[1]);
	while (env[i])
	{
		var2 = init_env_variable();
		var1->next_entry = var2;
		var1 = var2; 
		split_str = ft_split(env[i], '=');
		write_to_env_variable(var1, split_str[0], split_str[1]);
		free(split_str[2]);
		i++;
	}
}

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

int export_check_if_valid(char *arg)
{
	int i;

	i = 0;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		if (ft_isalpha(arg[i]) != 0 && (arg[i] != '_' && ft_strlen(arg) > 1))
			return (0);
		i++;
	}
	return (1);
}

int export(t_dict *dict, char *arg)
{
	t_dict *var;
	t_dict *last;
	char **split_str;
	char *new_key;
	char *new_value;

	if (arg == NULL)
	{
		while (dict)
		{
			printf("%s=%s\n", dict->key, dict->value);
			dict = dict->next_entry;
		}	
	}
	else
	{
		if (export_check_if_valid(arg) == 1)
		{
			printf("export: not an identifier %s\n", arg);
			return (1);
		}	
		split_str = ft_split(arg, '=');
		new_key = split_str[0];
		new_value = split_str[1];
		free(split_str[2]);
		var = search_key_in_dict(dict, new_key);
		if (var != NULL)
			write_to_env_variable(var, var->key, new_value);
		else
		{
			var = init_env_variable();
			last = get_dict_last(dict);	
			write_to_env_variable(var, new_key, new_value);
			last->next_entry = var;
		}
	}
	return (0);
}

/*
int main(int argc, char **argv, char **env)
{
	t_dict *dict;

	dict = init_env_variable();
	create_dict_on_startup(dict, env);

	export(dict, "_");
	export(dict, "_l");
	export(dict, "12345");
	export(dict, "new_var");
	export(dict, "new_var=100");
	//export(dict, NULL);
}
*/
