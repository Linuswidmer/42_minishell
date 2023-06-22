/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_free_cmdnode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:27:42 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/22 15:11:52 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void min_free_cmdnode(t_cmdnode       **cmdnode, int exit)
{
	t_cmdnode *curr;
	t_cmdnode *next;

	next = *cmdnode;
	while (next)
	{
		curr = next;
		next = next->next;
		if (exit)
			min_free(&curr->arg);
		free(curr);
	}
	*cmdnode = NULL;
}
