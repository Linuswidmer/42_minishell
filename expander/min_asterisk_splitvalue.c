/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_asterisk_splitvalue.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:02:16 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/22 15:57:15 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_add_last_expander(t_expander **word, char *value,
				t_lexertype key)
{
	t_expander	*end;

	if (!*word)
	{
		*word = min_init_expander(key, value);
		if (!*word)
			return (1);
	}
	else
	{
		end = min_last_expander(*word);
		end->next = min_init_expander(key, value);
		if (!(*word)->next)
		{
			min_free_expander(word);
			return (1);
		}
	}
	return (0);
}

static void	ft_get_dollar_asterisk(char **values, char space, t_expander **old)
{
	int	n;

	if (!values)
	{
		*old = NULL;
		return ;
	}
	n = 0;
	if (space == 1 || space == 3)
		ft_add_last_expander(old, EMPTY, l_asterisk);
	if ((space == 1 || space == 3) && (!old || !values[n]))
		return ;
	ft_add_last_expander(old, values[n], l_word);
	while (old && values[++n])
	{
		ft_add_last_expander(old, EMPTY, l_asterisk);
		if (old)
			ft_add_last_expander(old, values[n], l_word);
	}
	if (old && (space == 2 || space == 3))
		ft_add_last_expander(old, EMPTY, l_asterisk);
}

/* make from str asterisk and check for last entry in asterisk row*/
t_expander	*min_asterisk_splitvalue(char *value)
{
	char		**values;
	char		space;
	t_expander	*old;

	old = NULL;
	space = 0;
	values = min_delimiter_split(value, &space, E_ASTERISK);
	ft_get_dollar_asterisk(values, space, &old);
	min_dfree(&values);
	if (!old)
		ft_putstr_fd(ERR_MALL, 2);
	return (old);
}
