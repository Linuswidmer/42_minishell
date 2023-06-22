/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_check_dict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:12:59 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/22 12:14:55 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	min_check_dict(char **dollar, char **value, t_dict *dict)
{
	while (dict)
	{
		if (!ft_strncmp(dict->key, *dollar, ft_strlen(*dollar))
			&& ft_strlen(*dollar) == ft_strlen(dict->key))
			break ;
		else
			dict = dict->next_entry;
	}
	min_free(dollar);
	if (!dict)
		return (0);
	*value = ft_strdup(dict->value);
	return (1);
}
