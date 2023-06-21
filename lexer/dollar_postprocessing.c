/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_postprocessing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:42:52 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/21 16:09:39 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_quote_flag(t_lexertype key)
{
	if (key == l_dollar_q)
		return (1);
	return (0);
}

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

t_lexer	*dollar_postprocessing_loop(t_lexer *tmp,
							char *dollar_value, int quote_flag)
{
	int	pos;
	int	start;

	pos = 0;
	start = 0;
	while (dollar_value[pos] != '\0')
	{
		if (dollar_value[pos] == '$')
		{
			tmp = add_to_token_list(tmp, "q", 0, quote_flag);
			tmp->prev->key = l_dollar;
			start++;
			pos = postprocessing_var(dollar_value, pos + 1);
		}
		else
			pos = processing_word(dollar_value, pos);
		if (pos > start)
		{
			tmp = add_to_token_list(tmp, dollar_value, start, pos);
			tmp->prev->key = l_word;
		}
		start = pos;
	}
	return (tmp);
}

t_lexer	*dollar_postprocessing(t_lexer *tmp)
{
	char	*dollar_value;
	int		quote_flag;

	quote_flag = set_quote_flag(tmp->key);
	dollar_value = tmp->value;
	tmp = dollar_postprocessing_loop(tmp, dollar_value, quote_flag);
	free(dollar_value);
	if (tmp->key == l_empty)
		tmp = remove_token_from_list_end(tmp);
	return (tmp);
}
