/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_fit_to_asterisk.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:39:21 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/22 12:46:52 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_word_in_filename(char **filename, char *word, t_expander *curr)
{
	if (!**filename)
		return (0);
	while (**filename && *word)
	{
		if (*(*filename)++ != *word++)
			return (0);
	}
	if (!**filename && !*word)
		return (1);
	if (!*word && curr->next)
		return (1);
	else
		return (0);
}

static int	ft_last_word(char *filename, char *word)
{
	int	lena;
	int	lenb;

	lena = (int)ft_strlen(filename) -1;
	lenb = (int)ft_strlen(word) -1;
	if (!*filename)
		return (0);
	while (lena >= 0 && lenb >= 0)
	{
		if (filename[lena] == word[lenb])
		{
			lena--;
			lenb--;
		}
		else
			return (0);
	}
	if (lena == -1 && lenb >= 0)
		return (0);
	return (1);
}

static int	ft_is_asterisk(char **filename, t_expander **word, char *first)
{
	if (!(*first)++)
	{
		if (**filename == '.')
			return (0);
	}
	while ((*word)->key == l_asterisk)
	{
		if (!(*word)->next)
			return (1);
		*word = (*word)->next;
	}
	while (**filename && **filename != ((*word)->word)[0])
		(*filename)++;
	return (2);
}

static int	ft_is_word(char **filename, t_expander **word, char *first)
{
	(*first)++;
	if (!(*word)->next)
	{
		if (!ft_last_word(*filename, (*word)->word))
			return (0);
		else
			return (1);
	}
	if (!ft_word_in_filename(filename, (*word)->word, *word))
		return (0);
	*word = (*word)->next;
	return (2);
}

int	min_fit_to_asterisk(char *filename, t_expander *word)
{
	char	first;
	int		re;

	first = 0;
	while (word && filename)
	{
		if (word->key == l_asterisk)
		{
			re = ft_is_asterisk(&filename, &word, &first);
			if (re != 2)
				return (re);
		}
		else if (word->key == l_word)
		{
			re = ft_is_word(&filename, &word, &first);
			if (re != 2)
				return (re);
		}
		else
			word = word->next;
	}
	return (1);
}
