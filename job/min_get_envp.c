/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_get_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:31:15 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/29 14:57:06 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calc_dict_len(t_dict *dict)
{
	int	i;

	i = 0;
	while (dict)
	{
		i++;
		dict = dict->next_entry;
	}
	return (i);
}

char *const	*ft_get_envp(t_dict *dict)
{
	int		i;
	int		dict_len;
	char	**envp;
	int		entry_len;

	i = 0;
	dict_len = calc_dict_len(dict);
	envp = malloc(sizeof(char *) * (dict_len + 2));
	while (i < dict_len)
	{
		entry_len = ft_strlen(dict->key) + ft_strlen(dict->value) + 2;
		envp[i] = malloc(sizeof(const char) * entry_len);
		ft_bzero(envp[i], entry_len);
		ft_strlcat(envp[i], dict->key, entry_len);
		ft_strlcat(envp[i], "=", entry_len);
		ft_strlcat(envp[i], dict->value, entry_len);
		dict = dict->next_entry;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
