/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_token_is_para.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:55:27 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/07 18:05:30 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	min_token_is_para(t_lexertype key)
{
	if (key == l_paraopen)
		return (1);
	else if (key == l_paraclose)
		return (2);
	else
		return (0);
}
