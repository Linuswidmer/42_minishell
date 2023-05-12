/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:18:08 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/12 11:52:51 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_dict_export(t_dict *dict)
{
    while (dict)
    {
		if (dict->value)
        	printf("declare -x %s=\"%s\"\n", dict->key, dict->value);
        else
        	printf("declare -x %s=\"\"\n", dict->key);
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

char **split_export(char *arg)
{
	int		i;
	char	**split_str;

	i = 0;
	split_str = malloc(sizeof(char *) * 3);
	while (arg[i] != '=' && arg[i] != '\0')
		i++;
	split_str[0] = ft_substr(arg, 0, i);
	if (!(split_str[0]))
		return (NULL);
	if (i < ft_strlen(arg))
	{
		split_str[1] = ft_substr(arg, i + 1, ft_strlen(arg));
		if (!(split_str[1]))
			return (NULL);
	}
	else
		split_str[1] = NULL;
	split_str[2] = NULL;
	return (split_str);
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
	split_str = split_export(arg);
	if (!split_str)
		return (1);
	new_key = split_str[0];
	new_value = split_str[1];
	free(split_str[2]);
	var = search_key_in_dict(dict, new_key);
	if (var != NULL)
		write_to_dict(var, var->key, new_value);
	else
	{
		if (new_value)
			write_new_entry_to_dict(dict, new_key, new_value);
		else
			write_new_entry_to_dict(dict, new_key, NULL);
	}
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
