/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_free_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:54:51 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/22 11:19:20 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	min_free_expander(t_expander **node)
{
	t_expander *temp;
	t_expander *new;
	
	new = *node;
	
	while (new)
	{
		temp = new;
		new = new->next;
		min_free(&temp->word);
		free(temp);
		temp = NULL;
	}
	*node = NULL;
}		
