/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:18:08 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/02 10:11:45 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_dict_export(t_dict *dict)
{
    while (dict)
    {   
        printf("%s=%s\n", dict->key, dict->value);
        dict = dict->next_entry;
    }   
}

static int export_check_if_key_is_valid(char *arg)
{
	int i;
	int j;
	int only_digits_flag;

	i = 0;
	j = 0;
	only_digits_flag = 1;
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
	while (arg[j] != '=' && arg[j] != '\0')
	{
		if (ft_isalpha(arg[j]) != 0 || arg[j] == '_')
			only_digits_flag = 0;
		j++;
	}
	if (only_digits_flag == 1)
		return (1);
	else
		return (0);
}

int min_export(t_dict *dict, char **arg)
{
	t_dict *var;
	t_dict *last;
	char **split_str;
	char *new_key;
	char *new_value;
	int i;
	int exit;

	i = 0;
	exit = 1000;
	printf("enters export\n");
	if (!dict)
	{
		printf("no dictionary\n");
		return (1002);
	}
	if (arg[0] == NULL)
	{
		print_dict_export(dict);
		return (1000);
	}
	else
	{
		while (arg[i])
		{
			if (export_check_if_key_is_valid(arg[i]) == 1)
			{
				exit = 1002;
				printf("export: not an identifier %s\n", arg[i]);
			}
			else
			{
				split_str = ft_split(arg[i], '=');
				new_key = split_str[0];
				new_value = split_str[1];
				free(split_str[2]);
				var = search_key_in_dict(dict, new_key);
				if (var != NULL)
					write_to_dict(var, var->key, new_value);
				else
				{
					var = init_env_variable();
					last = get_dict_last(dict);	
					write_to_dict(var, new_key, new_value);
					last->next_entry = var;
				}
			}
			i++;
		}
	}
	return (exit);
}
