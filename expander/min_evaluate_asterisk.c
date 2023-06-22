/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_evaluate_asterisk.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:36:42 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/22 17:46:05 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_notfound(t_expander *asterisk)
{
	char	*value;
	char	*temp;

	value = ft_strjoin(EMPTY, EMPTY);
	while (value && asterisk)
	{
		temp = value;
		if (asterisk->key == l_asterisk)
			value = ft_strjoin(temp, ASTERISK);
		else
			value = ft_strjoin(temp, asterisk->word);
		min_free(&temp);
		asterisk = asterisk->next;
	}
	return (value);
}

void	min_evaluate_asterisk(t_expander **word, t_expander *asterisk, char wo)
{
	struct dirent	*d;
	DIR				*dh;
	char			found;
	char		*temp;

	dh = opendir("./");
	d = readdir(dh);
	found = 0;

	while (d)
	{
		if (min_fit_to_asterisk(d->d_name, asterisk))
		{
			found = 1;
			temp = strdup(d->d_name);
			if (min_addlast_expander(word, temp, &wo))
				break ;
		}			
		d = readdir(dh);
	}
	if (!found)
		min_addlast_expander(word, ft_notfound(asterisk), &wo);
	free (dh);
}
