/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_init_exphelp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:57:25 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/22 12:58:09 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exphelp	min_init_exphelp(t_dict *dict, char word, char space )
{
	t_exphelp	help;

	ft_bzero(&help, sizeof(t_exphelp));
	help.dict = dict;
	if (word)
		help.word = word;
	if (space)
		help.space = space;
	return (help);
}
