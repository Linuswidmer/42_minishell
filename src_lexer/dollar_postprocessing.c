/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_postprocessing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:42:52 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/11 10:20:43 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	postprocessing_var(char *str, int pos)
{
	if (str[pos] == '?')
		return (pos + 1);
	else if (str[pos] == '$')
		return (pos);
	else
	{
		while (ft_isalnum(str[pos]) != 0 || str[pos] == '_')
			pos++;
	}
	return (pos);
}

int	processing_word(char *str, int pos)
{
	while (str[pos] != '$' && str[pos] != '\0')
		pos++;
	return (pos);
}

t_lexer	*dollar_postprocessing(t_lexer *tmp)
{
	t_lexer	*tmp2;
	char	*dollar_value;
	int		pos;
	int		start;

	pos = 0;
	start = 0;
	dollar_value = tmp->value;
	tmp->value = NULL;
	while (dollar_value[pos] != '\0')
	{
		if (dollar_value[pos] == '$')
		{
			tmp = add_to_token_list(tmp, l_dollar, NULL, 0, 0);
			start++;
			pos = postprocessing_var(dollar_value, pos + 1);
		}
		else
			pos = processing_word(dollar_value, pos);
		if (pos > start)
			tmp = add_to_token_list(tmp, l_word, dollar_value, start, pos);
		start = pos;
	}
	free(dollar_value);
	if (tmp->key == l_empty)
		tmp = remove_token_from_list_end(tmp);
	return (tmp);
}
