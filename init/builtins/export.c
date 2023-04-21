/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:18:08 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/20 16:58:07 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "../init.h"

void    print_dict_export(t_dict *dict)
{
    while (dict)
    {   
        printf("%s=%s\n", dict->key, dict->value);
        dict = dict->next_entry;
    }   
}

int export_check_if_key_is_valid(char *arg)
{
	int i;

	i = 0;
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

	i = 0;
	if (arg == NULL)
		print_dict_export(dict);
	else
	{
		while (arg[i])
		{
			if (export_check_if_key_is_valid(arg[i]) == 1)
				printf("export: not an identifier %s\n", arg[i]);
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
