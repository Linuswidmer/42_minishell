/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_last_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:51:51 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/14 12:54:17 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expander *min_last_expander(t_expander *node)
{
	while (node && node->next)
		node = node->next;
	return (node);
}
