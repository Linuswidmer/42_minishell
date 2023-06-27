/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_init_subnode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:44:46 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/23 18:49:56 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*min_init_subnode(void)
{
	t_ast	*sub;

	sub = (t_ast *)malloc(sizeof(t_ast));
	if (!sub)
		return (NULL);
	ft_bzero(sub, sizeof(t_ast));
	sub->key = subnode;
	sub->u_no.sub = (t_subnode *)malloc(sizeof(t_subnode));
	if (!sub->u_no.sub)
		return (NULL);
	ft_bzero(sub->u_no.sub, sizeof(t_subnode));
	return (sub);
}
