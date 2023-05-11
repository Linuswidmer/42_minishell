/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:18:08 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/10 11:58:44 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_dict_export(t_dict *dict)
{
    while (dict)
    {   
        printf("declare -x %s=\"%s\"\n", dict->key, dict->value);
        dict = dict->next_entry;
    }   
}

static int	export_check_if_key_is_valid(char *arg)
{
	int	i;
	int	j;
	int	only_digits_flag;

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

int export_new_entry(t_dict *dict, char *arg)
{
	int		exit;
	t_dict	*var;
	char	**split_str;
	char	*new_key;
	char	*new_value;

	/* wie mache ich das hier, wenn ein malloc failed? sollte dann die ganze
	Minishell abbrechen? wir riskieren sonst leaks*/
	split_str = ft_split(arg, '=');
	if (!split_str)
		return (1);
	new_key = split_str[0];
	new_value = split_str[1];
	free(split_str[2]);
	var = search_key_in_dict(dict, new_key);
	if (var != NULL)
		write_to_dict(var, var->key, new_value);
	else
		write_new_entry_to_dict(dict, new_key, new_value);
	return (0);
}

int	min_export(t_dict *dict, char **arg)
{
	int		i;
	int		exit;
	int		status;

	i = 0;
	status = 0;
	exit = 0;
	if (!dict)
	{
		ft_printf_fd("no dictionary\n", 2);
		return (1002);
	}
	if (arg[0] == NULL)
		print_dict_export(dict);
	else
	{
		while (arg[i])
		{
			if (export_check_if_key_is_valid(arg[i]) == 1)
			{
				ft_printf_fd("export: not a valid identifier %s\n", 2, arg[i]);
				status = 1;
			}
			else
				status = export_new_entry(dict, arg[i]);
			if (!exit)
				exit = status;
			i++;
		}
	}
	return (exit + 1000);
}
