/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_token_is_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:32:27 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/17 13:21:27 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"


int	min_token_is_word(t_lexertype key)
{
	if (key == l_word
		return (1); 
	if (key == l_dollar)
		return (2);
	if  (key == l_asterisk)
       return(3);
	else
		return (0);
}
