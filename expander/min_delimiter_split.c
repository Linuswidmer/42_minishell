/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_delimiter_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:21:23 by lwidmer           #+#    #+#             */
/*   Updated: 2023/07/05 12:31:56 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**min_delimiter_split(char *value, char *space, char delimiter)
{
	if (!value)
		return (NULL);
	if (*space || *value == delimiter)
		*space = 1;
	if (ft_strlen(value) && value[ft_strlen(value) - 1] == delimiter)
		*space += 2;
	return (ft_split(value, delimiter));
}
