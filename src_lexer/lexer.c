/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:54:21 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/10 10:18:41 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer *lexer(char *input)
{
  int start;
  int pos;
  int len_input;
  t_lexertype current_token;
  t_lexer *tmp;
  t_lexer *tmp2;
  t_lexer *beginning_token_list;

	beginning_token_list = init_lexer_struct();
	if (!beginning_token_list)
		return (NULL);
	tmp = beginning_token_list;
	start = 0;
	pos = 0;
	len_input = ft_strlen(input);
	while (pos < len_input)
	{
		current_token = check_token(input[pos], input[pos + 1]);
		pos = parse_token_to_list(current_token, input, pos, tmp, start);
		if (pos < 0)
		{
			free_token_list(beginning_token_list);
			return (NULL);
		}
		pos = skip_space_tab(input, pos);
		start = pos;
		if (tmp->key != l_empty && pos < len_input)
		{
			tmp2 = init_lexer_struct();
			if (!tmp2)
			{
				free_token_list(beginning_token_list);
				return (NULL);
			}
			tmp->next = tmp2;
			tmp2->prev = tmp;
			tmp = tmp2;
		}
	}
	return(beginning_token_list);
}
