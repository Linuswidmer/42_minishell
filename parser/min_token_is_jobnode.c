/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_token_is_jobnode.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 07:22:50 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/11 07:28:46 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int min_token_is_jobnode(t_lexertype key)
{
	if (min_token_is_io(key) || min_token_is_word(key)
		|| key == l_space)
		return (1);
	else
		return (0);
}
