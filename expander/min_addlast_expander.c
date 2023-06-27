/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_addlast_expander.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:06:02 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/27 12:48:19 by jstrotbe         ###   ########.fr       */
/*   Updated: 2023/06/22 11:21:59 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	min_addlast_expander(t_expander **word, char *value, char *wo, char free)
{
	t_expander	*end;

	end = min_last_expander(*word);
	if (wo && *wo)
	{
		min_free(&end->word);
		end->key = l_word;
		end->word = value;
		*wo = 0;
	}
	else
	{
		end->next = min_init_expander(l_word, ft_strdup(value));
		if (free)
			min_free(&value);
		if (!(*word)->next)
		{
			min_free_expander(word);
			return (1);
		}
	}
	return (0);
}
