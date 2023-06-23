/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_dfree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:06:27 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/23 15:06:56 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	min_dfree(char ***tofree)
{
	int	i;

	i = 0;
	if (*tofree)
	{
		while ((*tofree)[i])
		{
			min_free(&((*tofree)[i]));
			i++;
		}
		free(*tofree);
		*tofree = NULL;
	}
}
