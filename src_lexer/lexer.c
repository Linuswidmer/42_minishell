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

t_lexer *dollar_postprocessing(t_lexer *tmp)
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
			if (dollar_value[pos] == '?')
				pos++;
			else if (dollar_value[pos] == '$')
				continue ;
			else
			{
				while (isalnum(dollar_value[pos]) != 0)
					pos++;
			}
			if (pos > start)
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

int heredoc_get_limiter(t_lexer *token_list, t_lexer **limiter)
{
	while (token_list->key == l_space)
		token_list = token_list->next;
	if (token_list->key == l_word)
	{
		*limiter = token_list;
		return (0);
	}
	else
		return (1);
}

int evaluate_heredoc(t_lexer *token_list)
{
	int fd;
	int n;
	t_lexer *limiter;
	char *str;
	char *tmpname;
	t_lexer *tmp;
	int heredoc_count;

	heredoc_count = 0;
	while (token_list)
	{
		if (token_list->key == l_heredoc)
		{
			tmpname = malloc(sizeof(char) * 6);
			tmpname[0] = '.';
			tmpname[1] = 't';
			tmpname[2] = 'm';
			tmpname[3] = 'p';
			tmpname[4] =  heredoc_count + 48;
			tmpname[5] = '\0';
			fd = open(tmpname, O_CREAT | O_WRONLY | O_TRUNC);
			heredoc_get_limiter(token_list->next, &limiter);
			while (1)
			{
				str = get_next_line(0);
				printf("str ist %s\n", str);
				printf("limiter is %s\n", limiter->value);
				printf("%i\n",ft_strncmp(str, limiter->value, ft_strlen(str)));
				if (ft_strncmp(str, limiter->value, ft_strlen(str) - 1) == 0)
					break ;
				write(fd, str, ft_strlen(str));
				free (str);
			}
			token_list->key = l_in;
			free(limiter->value);
			limiter->value = tmpname;
			heredoc_count ++;
		}
		token_list = token_list->next;
	}
	return (0);
}

t_lexer *lexer(char *input)
{
	int		token_exit_status;
	char	*new_input;
	t_lexer *beginning_token_list;


	beginning_token_list = init_lexer_struct();
	if (!beginning_token_list)
		return (NULL);
	token_exit_status = create_token_list(input, beginning_token_list);
	while (token_exit_status < 0)
	{
		new_input = readline(">");
		ft_strlcat(input, new_input, ft_strlen(input) + ft_strlen(new_input) + 1);
		// free previous token list
		beginning_token_list = init_lexer_struct();
		token_exit_status = create_token_list(input, beginning_token_list);
	}
	print_token_list(beginning_token_list);
	evaluate_heredoc(beginning_token_list);
	return (beginning_token_list);
}
