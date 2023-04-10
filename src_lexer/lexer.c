/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:54:21 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/10 12:07:30 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	create_token_list(char *input, t_lexer *tmp)
{
	int start;
	int pos;
	int len_input;
	t_lexertype current_token;
	t_lexer *tmp2;

	start = 0;
	pos = skip_space_tab(input, 0);
	len_input = ft_strlen(input);
	while (pos < len_input)
	{
		current_token = check_token(input[pos], input[pos + 1]);
		pos = parse_token_to_list(current_token, input, pos, tmp, start);
		if (pos < 0)
			return (pos);
		pos = skip_space_tab(input, pos);
		start = pos;
		if (tmp->key != l_empty && pos < len_input)
		{
			tmp2 = init_lexer_struct();
			if (!tmp2)
				return (-1);
			tmp->next = tmp2;
			tmp2->prev = tmp;
			tmp = tmp2;
		}	
	}
	return (0);
}

t_lexer *lexer(char *input)
{
	int		token_exit_status;
	t_lexer *beginning_token_list;

	beginning_token_list = init_lexer_struct();
	if (!beginning_token_list)
		return (NULL);
	token_exit_status = create_token_list(input, beginning_token_list);
	if (token_exit_status == -1)
		printf("Malloc failed\n");
	else if (token_exit_status == -2)
		printf("Quotes left open\n");
	return (beginning_token_list);
}
/*
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
	pos = skip_space_tab(input, 0);
	len_input = ft_strlen(input);
	while (pos < len_input)
	{
		current_token = check_token(input[pos], input[pos + 1]);
		pos = parse_token_to_list(current_token, input, pos, tmp, start);
		if (pos == -1)
		{
			free_token_list(beginning_token_list);
			return (NULL);
		}
		else if (pos == -2)
			printf("quotes left open\n");
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
*/
