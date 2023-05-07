/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:54:21 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/08 00:16:16 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
if end of input is reached and quotes have not been closed, the function 
returns -1 or -2 if it is a quote or dquote respectively
-3 is exit code for a failed malloc
*/
int	create_token_list(char *input, t_lexer *tmp)
{
	int			start;
	int			pos;
	t_lexertype	current_token;
	t_lexer		*tmp2;

	start = 0;
	pos = 0;
	while (pos < ft_strlen(input) && pos >= 0)
	{
		current_token = check_token(input, pos);
		pos = parse_token_to_list(current_token, input, pos, tmp, start);
		start = pos;
		if (tmp->key == l_dollar)
			tmp = dollar_postprocessing(tmp);
		if (tmp->key != l_empty && pos < ft_strlen(input) && pos > 0)
		{
			tmp2 = init_lexer_struct();
			if (!tmp2)
				return (-3);
			tmp->next = tmp2;
			tmp2->prev = tmp;
			tmp = tmp2;
		}	
	}
	return (pos);
}

char	*readline_prompt_quotes(int quotetype)
{
	char	*input;

	if (quotetype == 1)
		return (input = readline("dquote>"));
	else if (quotetype == 2)
		return (input = readline("quote>"));
	else
		return (NULL);
}

t_lexer	*lexer(char **input)
{
	int		token_exit_status;
	char	*new_input;
	char	*new_input2;
	t_lexer	*beginning_token_list;

	beginning_token_list = init_lexer_struct();
	if (!beginning_token_list)
		return (NULL);
	token_exit_status = create_token_list(*input, beginning_token_list);
	if (token_exit_status == -3)
		free_token_list(&beginning_token_list);
	while (beginning_token_list && token_exit_status < 0)
	{
		new_input = readline_prompt_quotes(-token_exit_status);
		new_input2 = ft_strjoin(*input, new_input);
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
