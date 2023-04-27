/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_last_cmdnode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:30:10 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/17 14:24:11 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

t_cmdnode *min_last_cmdnode(t_cmdnode *node)
{
        while (node->next)
                node = node->next;
    return (node);
}
