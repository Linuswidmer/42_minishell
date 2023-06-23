/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_is_last_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:46:04 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/23 17:02:27 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	min_is_last_token(t_lexer *token)
{
	token = token->next;
	while (token && token->key == l_space)
		token = token->next;
	if (token)
		return (0);
	else
		return (1);
}
