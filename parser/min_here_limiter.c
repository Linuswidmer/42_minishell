/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_here_limiter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:40:51 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/23 16:48:10 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_limiter_loop(t_lexer *token, char *limiter)
{
	char	*temp;
	char	*temp2;

	temp2 = ft_strdup(limiter);
	while (temp2 && token && min_token_is_word(token->key))
	{
		temp = temp2;
		if (min_token_is_word(token->key) == 2)
			temp2 = ft_strjoin(temp2, DOLLAR);
		else if (min_token_is_word(token->key) == 3)
			temp2 = ft_strjoin(temp2, ASTERISK);
		else
			temp2 = ft_strjoin(temp2, token->value);
		token = token->next;
		min_free(&temp);
	}
	limiter = ft_strdup(temp2);
	min_free(&temp2);
	return (limiter);
}

char	*min_here_limiter(t_lexer *token)
{
	while (token && token->key == l_space)
		token = token->next;
	if (!token)
		min_parser_error(NULL, 0, P_NEWLINE);
	if (token && min_token_is_word(token->key))
		return (ft_limiter_loop(token, EMPTY));
	else
		return (NULL);
}
