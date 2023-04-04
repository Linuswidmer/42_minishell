/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_token_is_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:32:27 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/04 15:56:52 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"


int	min_token_is_word(t_lexertype key)
{
	if (key == word || key == asterix)
		return(1);
	else
		return (0);
}
