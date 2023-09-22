/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:25:40 by lwidmer           #+#    #+#             */
/*   Updated: 2023/07/06 15:17:51 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_to_dict(t_dict *entry, char *arg)
{
	char	**split_str;
	int		i;

	i = 0;
	if (!arg || !entry)
		return (1);
	split_str = malloc(sizeof(char *) * 3);
	if (!split_str)
		return (1);
	while (arg[i] != '\0' && arg[i] != '=')
		i++;
	split_str[0] = ft_substr(arg, 0, i);
	split_str[1] = ft_substr(arg, i + 1, ft_strlen(arg));
	split_str[2] = NULL;
	write_to_dict(entry, split_str[0], split_str[1]);
	free(split_str[0]);
	if (split_str[1])
		free(split_str[2]);
	free(split_str[1]);
	free(split_str);
	return (0);
}

int	create_dict_on_startup(char **env, t_dict **p_dict)
{
	t_dict	*var1;
	t_dict	*var2;
	int		i;
	int		exit;

	i = 1;
	var1 = init_env_variable();
	if (!var1)
		return (1);
	*p_dict = var1;
	exit = str_to_dict(var1, env[0]);
	while (env[i] && !exit)
	{
		var2 = init_env_variable();
		if (!var2)
			return (1);
		var1->next_entry = var2;
		var1 = var2;
		exit = str_to_dict(var1, env[i]);
		i++;
	}
	exit = min_update_shlvl_on_startup(*p_dict);
	return (exit);
}
