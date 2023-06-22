/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_free_cmdnode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:27:42 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/22 09:46:54 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void min_free_cmdnode(t_cmdnode       **cmdnode)
{
	t_cmdnode *curr;
	t_cmdnode *next;

	next = *cmdnode;
	while (next)
	{
		curr = next;
		next = next->next;
		//min_free(&curr->arg);
		free(curr);
	}
	*cmdnode = NULL;
}
