/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_init_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:47:07 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/22 10:47:02 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expander	*min_init_expander(t_lexertype key, char *value)
{
	t_expander	*new;

	new = (t_expander *)malloc(sizeof(t_expander));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_expander));
	new->key = key;
	new->word = ft_strdup(value);
	if (!new->word && value)
		return (NULL);
	return (new);
}
