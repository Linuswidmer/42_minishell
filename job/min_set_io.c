/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_set_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:05:57 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/27 10:06:38 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*ft_set_filename(t_lexer **token, t_dict *dict)
{
	char	**values;
	char	*filename;

	values = min_word_eval(token, dict);
	if (!values)
		return (NULL);
	if (values[1])
	{
		ft_printf_fd(TMOPEN, 2);
		min_dfree(&values);
		return (NULL);
	}
	filename = ft_strdup(values[0]);
	min_dfree(&values);
	return (filename);
}

static char	*ft_set_file_io(t_lexer **token, t_dict *dict)
{
	while (*token)
	{
		if (min_token_is_word((*token)->key))
			return (ft_set_filename(token, dict));
		else if ((*token)->key == l_space)
			*token = (*token)->next;
	}
	return (NULL);
}

int	min_set_io(t_lexer **token, t_dict *dict)
{
	t_lexertype	key;
	char		*filename;
	char		*evalhere;

	key = (*token)->key;
	evalhere = (*token)->value;
	*token = (*token)->next;
	filename = ft_set_file_io(token, dict);
	if (!filename)
		return (1);
	return (min_ex_io(key, filename, evalhere));
}
