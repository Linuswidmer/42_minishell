/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_last_ionode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:29:06 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/07 12:57:24 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parser.h"


t_ionode *min_last_ionode(t_ionode *node)
{
        while (node->next)
                node = node->next;
    return (node);
}
