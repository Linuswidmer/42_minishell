/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_token_is_route.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:59:01 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/05 20:00:40 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.c"

int min_token_is_route(t_lexertype key)
{
	if (key == and || key == or || key == semi)
		return (1);
	else
		return (0);
}
