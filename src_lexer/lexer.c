/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:54:21 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/21 13:34:32 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_token_list(char *input, t_lexer *tmp)
{
	int start;
	int pos;
	int len_input;
	t_lexertype current_token;
	t_lexer *tmp2;

	start = 0;
	pos = 0;
	len_input = ft_strlen(input);
	while (pos < len_input)
	{
		current_token = check_token(input[pos], input[pos + 1]);
		pos = parse_token_to_list(current_token, input, pos, tmp, start);
		if (pos < 0)
			return (pos);
		start = pos;
		if (tmp->key == l_dollar)
			tmp = dollar_postprocessing(tmp);
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


t_lexer *lexer(char **input)
{
	int		token_exit_status;
	char	*new_input;
	char	*new_input2;
	t_lexer *beginning_token_list;

	beginning_token_list = init_lexer_struct();
	if (!beginning_token_list)
		return (NULL);
	token_exit_status = create_token_list(*input, beginning_token_list);
	while (token_exit_status < 0)
	{
		new_input = readline(">");
		new_input2 = ft_strjoin(*input, new_input);
		printf("new_input2 is %s\n", new_input2);
		free_token_list(&beginning_token_list);
		beginning_token_list = init_lexer_struct();
		token_exit_status = create_token_list(new_input2, beginning_token_list);
		free(*input);
		free(new_input);
		*input = new_input2;
	}
	print_token_list(beginning_token_list);
	return (beginning_token_list);
}
