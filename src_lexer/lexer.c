/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:54:21 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/15 11:21:14 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer *add_to_token_list(t_lexer *list_end, t_lexertype key, char *str, int start, int pos)
{
	t_lexer *new_list_end;

	new_list_end = init_lexer_struct();
	new_list_end->prev = list_end;
	list_end->next = new_list_end;
	list_end->key = key;
	if (str)
		list_end->value = ft_substr(str, start, pos - start);
	return (new_list_end);
}

t_lexer *remove_token_from_list_end(t_lexer *list_end)
{
	t_lexer *new_list_end;

	new_list_end = list_end->prev;
	new_list_end->next = NULL;
	if (list_end->value)
		free(list_end->value);
	free(list_end->value);
	free(list_end);
	return (new_list_end);

}

t_lexer *dollar_pastprocessing(t_lexer *tmp)
{
	t_lexer *tmp2;
	char *dollar_value;
	int pos;
	int start;

	pos = 0;
	start = 0;
	dollar_value = tmp->value;
	tmp->value = NULL;
	while (dollar_value[pos] != '\0')
	{
		if (dollar_value[pos] == '$')
		{
			tmp = add_to_token_list(tmp, l_dollar, NULL, 0, 0);
			pos++;
			start++;
			if (dollar_value[pos] == '$' || dollar_value[pos] == '?')
				pos++;
			else
			{
				while (isalnum(dollar_value[pos]) != 0)
					pos++;
			}
			tmp = add_to_token_list(tmp, l_word, dollar_value, start, pos);
			start = pos;
		}
		else
		{
			while (dollar_value[pos] != '$' && dollar_value[pos] != '\0')
				pos++;
			tmp = add_to_token_list(tmp, l_word, dollar_value, start, pos);
			start = pos;
		}
	}
	free(dollar_value);
	if (tmp->key == l_empty)
			tmp = remove_token_from_list_end(tmp);
	return (tmp);
}

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
			tmp = dollar_pastprocessing(tmp);
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
