/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_addlast_expander.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:06:02 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/12 16:22:35 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	min_addlast_expander(t_expander **word, char *value, char *wo)
{
	if (!*word)
	{
		*word = min_init_expander(l_word, d->d_name);
		if (!*word)
			return (1);
	}
	else
	{
		end = min_last_expander(*word);
        if (*wo)
        {
			end->key = l_word;
			end->word = value;
			*wo = 0;
		}
		else
		{
			end->next =  min_init_expander(l_word, value);
			if (!(*word)->next)
			{	
      			min_free_expander(word);
                return (1);
			}
         }
	}	 			
	return (0);            
}

