/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_add_value_to_expander.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:37:15 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/22 11:38:31 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	min_add_value_to_expander(t_lexer **token, t_expander **word,
									char **result, char space)
{
	if (!*result)
		min_free_expander(word);
	else
	{
		min_word(token, word, *result, space);
		min_free(result);
	}
	return (0);
}
