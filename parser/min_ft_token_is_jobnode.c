/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_ft_token_is_jobnode.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:22:22 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/07/05 18:28:29 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	min_ft_token_is_jobnode(t_lexertype key)
{
	if (min_token_is_io(key) || min_token_is_word(key))
		return (1);
	else
		return (0);
}
