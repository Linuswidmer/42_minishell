/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_token_is_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:32:27 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/07 13:17:08 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"


int	min_token_is_word(t_lexertype key)
{
	if (key == l_word || key == l_asterisk)
		return(1);
	else
		return (0);
}
