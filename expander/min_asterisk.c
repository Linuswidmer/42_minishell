/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_asterisk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:59:48 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/22 11:59:37 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_is_asterisk(t_expander *word)
{
	while (word && word->key != l_asterisk)
		word = word->next;
	if (!word)
		return (0);
	else
		return (1);
}

static void	ft_check_last_asterisk_entry(t_expander **old, t_expander *word)
{
	char		*oldword;
	t_expander	*temp;

	if ((*old)->key == l_word && (word && (min_last_expander(word))->key
			== l_word))
	{
		oldword = (*old)->word;
		(*old)->word = ft_strjoin((min_last_expander(word))->word, oldword);
		min_free(&oldword);
	}
	else
	{
		temp = *old;
		if (!ft_is_asterisk(word))
		{
			*old = min_init_expander((min_last_expander(word))->key,
					(min_last_expander(word))->word);
		}
		else
			*old = word;
		if (*old)
			(min_last_expander(*old))->next = temp;
	}
}

/* this can also handel if * are in $cmd  */
static void	ft_start_asterisk(t_expander *word, t_expander **asterisk,
								t_expander *old)
{
	if (word)
	{
		if (!old)
		{
			*asterisk = min_init_expander(l_word, word->word);
			if (*asterisk)
				(*asterisk)->next = min_init_expander(l_asterisk, NULL);
		}
		else
		{
			ft_check_last_asterisk_entry(&old, word);
			*asterisk = old;
		}
	}
	else if (old)
		*asterisk = old;
	else
		*asterisk = min_init_expander(l_asterisk, NULL);
}

/*
creates a link list with all asterisk  and evaluate it, 
if $ have more then one value gives back the zhe other values in extra  
help.word -> flag to show that before first apperace of * was an other word 
help.token -> flag to show if token can be used 
t_expander *old -> get the evaluatetet link list from a * in a $ARG 
-> this will be connectet to the fromer Asterisk or get evaluatett alone or 
with the next tokens 
*/
char	min_asterisk(t_lexer **token, t_expander **word, t_expander *old,
						t_exphelp help)
{
	t_expander	*asterisk;
	t_expander	*extra;

	if (!*word)
		return (1);
	if ((!help.space && (min_last_expander(*word))->key == l_word) || help.word)
		ft_start_asterisk(*word, &asterisk, old);
	else
		ft_start_asterisk(NULL, &asterisk, old);
	if ((!help.space && (min_last_expander(*word))->key == l_word)
		|| (*word)->key == l_empty)
		help.word = 1;
	if (token && asterisk)
		help.space = min_gaam(token, &asterisk, &extra, help.dict);
	if (asterisk)
		min_evaluate_asterisk(word, asterisk, help.word);
	if (token && asterisk)
		min_add_extra_to_word(word, extra);
	if (!asterisk)
		min_free_expander(word);
	min_free_expander(&asterisk);
	if (token)
		min_free_expander(&extra);
	return (help.space);
}
