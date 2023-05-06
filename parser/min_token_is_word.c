/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_token_is_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:32:27 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/05 10:32:03 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"


int	min_token_is_word(t_lexertype key)
{
	if (key == l_word)
		return (1); 
	if (key == l_dollar)
		return (2);
	if  (key == l_asterisk)
       		return(3);
	if (key == l_til)
			return (4);
	else
		return (0);
}
