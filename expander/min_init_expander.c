/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_init_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:47:07 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/14 15:58:34 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_expander *min_init_expander(t_lexertype key)
{
	t_expander *new;

	new = (t_expander *)malloc(sizeof(t_expander));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_expander));
	new->key = key;
	new->word = ft_strdup(EMPTY);
	if (!new->word)
		/* free !!! new */
		return (NULL);
	return (new);
} 
