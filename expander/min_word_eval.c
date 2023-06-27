/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_word_eval.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:38:59 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/27 12:45:43 by jstrotbe         ###   ########.fr       */
/*   Updated: 2023/06/22 11:06:58 by jstrotbe         ###   ########.fr       */
/*   Updated: 2023/05/11 11:40:55 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_values(t_expander *word)
{
	int	c;

	c = 1;
	while (word)
	{
		c++;
		word = word->next;
	}
	return (c);
}

static char	**ft_get_values(t_expander *word, t_exphelp help)
{
	int	count;

	if (!word)
		return (NULL);
	count = ft_count_values(word);
	help.splitvalue = ft_calloc(sizeof(char **), (count +1));
	if (!help.splitvalue)
		return (NULL);
	while (word)
	{
		help.splitvalue[help.n] = ft_strdup(word->word);
		if (!help.splitvalue[help.n++])
		{
			min_dfree(&help.splitvalue);
			word = NULL;
		}
		else
			word = word->next;
	}
	if (help.splitvalue)
		help.splitvalue[help.n++] = NULL;
	return (help.splitvalue);
}

/* */
char	**min_word_eval(t_lexer **token, t_dict *dict)
{
	char		**values;
	t_expander	*word;
	t_exphelp	help;

	help = min_init_exphelp(dict, 0, 0);
	word = min_init_expander(l_empty, ft_strdup(EMPTY));
	while (!help.space && word && *token && min_token_is_word((*token)->key))
	{
		if (min_token_is_word((*token)->key) == 1)
			help.space = min_word(token, &word, NULL, help.space);
		else if (min_token_is_word((*token)->key) == 2)
			help.space = min_dollar(token, &word, NULL, help);
		else if (min_token_is_word((*token)->key) == 4)
			help.space = min_til(token, &word, help);
		else if (min_token_is_word((*token)->key) == 3)
		{
			help.space = min_asterisk(token, &word, NULL, help);
		}
	}
	values = ft_get_values(word, help);
	min_free_expander(&word);
	return (values);
}
