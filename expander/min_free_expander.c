/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_free_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:54:51 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/14 13:01:18 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	min_free_expander(t_expander **node)
{
	t_expander *temp;
	
	while (*node)
	{
		temp = *node;
		*node = (*node)->next;
		gnl_free(&temp->word);
		free(temp);
		temp = NULL;
	}
}		
