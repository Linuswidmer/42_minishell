/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_token_is_io_in.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:00:43 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/07 15:39:10 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"	


int  min_token_is_io_in(t_lexertype key)
{
    if (key == l_in || key == l_heredoc)
        return (1);
    else
        return (0)
}

