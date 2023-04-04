/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_token_is_io.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:26:46 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/04 12:32:07 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"


int	min_token_is io(t_lexertype key)
{
	if (key == in || key == out || key == append || key == heredoc)
		return (1);
	else
		return (0);
