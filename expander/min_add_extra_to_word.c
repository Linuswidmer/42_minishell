/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_add_extra_to_word.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 10:31:40 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/22 10:31:42 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	min_add_extra_to_word(t_expander **word, t_expander *extra)
{
	if (!extra)
		return ;
	while (extra)
	{
		if (min_addlast_expander(word, extra->word, NULL))
			break ;
		extra = extra->next;
	}
}
