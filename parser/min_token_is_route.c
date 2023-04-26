/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_token_is_route.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:59:01 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/07 15:41:54 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int min_token_is_route(t_lexertype key)
{
	if (key == l_and)
		return (1);
	else if (key == l_or)
		return (2);
	else if (key == l_semi)
		return (3);
	else
		return (0);
}
