/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_token_is_io.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:26:46 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/07 15:38:15 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"


int	min_token_is_io(t_lexertype key)
{
	if (key == l_in)
		return (1);
	if (key == l_out)
		return (2);
	if (key == l_append)
		return (3);
	if (key == l_heredoc)	
		return (4);
	else
		return (0);
}
