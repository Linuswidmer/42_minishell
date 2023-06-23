/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:54:21 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/23 15:15:29 by lwidmer          ###   ########.fr       */
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
	size_t		pos;
	t_lexertype	current_token;
	t_lexer		*tmp2;

	start = 0;
	pos = 0;
	while (pos < ft_strlen(input) && pos >= 0)
	{
		current_token = check_token(input, pos);
		pos = parse_token_to_list(current_token, input, pos, tmp);
		start = pos;
		if ((tmp->key == l_dollar || tmp->key == l_dollar_q) && tmp->value)
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

char	*open_quotes_get_new_input(char **input, int quotetype)
{
	char	*new_input;
	char	*new_input2;

	new_input = NULL;
	if (quotetype == 1)
		new_input = readline("dquote>");
	else if (quotetype == 2)
		new_input = readline("quote>");
	if (!new_input)
		new_input = ft_strdup("");
	new_input2 = ft_strjoin(*input, new_input);
	free(new_input);
	free(*input);
	return (new_input2);
}

t_lexer	*lexer(char **input)
{
	int		token_exit_status;
	char	*new_input;
	t_lexer	*beginning_token_list;

	beginning_token_list = init_lexer_struct();
	if (!beginning_token_list)
		return (NULL);
	token_exit_status = create_token_list(*input, beginning_token_list);
	if (token_exit_status == -3)
		free_token_list(&beginning_token_list);
	while (beginning_token_list && token_exit_status < 0)
	{
		free_token_list(&beginning_token_list);
		beginning_token_list = init_lexer_struct();
		if (!beginning_token_list)
			return (NULL);
		new_input = open_quotes_get_new_input(input, -token_exit_status);
		token_exit_status = create_token_list(new_input, beginning_token_list);
		*input = new_input;
	}
	if (_DEBUG)
		print_token_list(beginning_token_list);
	return (beginning_token_list);
}
