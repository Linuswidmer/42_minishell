/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_here_set_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:48:57 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/23 17:01:27 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	ft_free_lexernode(t_lexer **token_list)
{
	if (*token_list)
	{
		if ((*token_list)->value)
			free((*token_list)->value);
		free(*token_list);
		*token_list = NULL;
	}
}

static void	ft_space(t_lexer **file)
{
	while (*file && (*file)->key == l_space)
	{
		if ((*file)->next)
		{
			*file = (*file)->next;
			ft_free_lexernode(&(*file)->prev);
		}
	}
}

static void	ft_word(t_lexer **file, t_lexer *token)
{
	while (*file && min_token_is_word((*file)->key))
	{
		if ((*file)->next)
		{
			*file = (*file)->next;
			if ((*file)->prev != token)
				ft_free_lexernode(&(*file)->prev);
		}
		else
		{
			if ((*file)->prev != token->prev)
				ft_free_lexernode(file);
			else
				*file = NULL;
			break ;
		}
	}
}

/* set path to next next wrd and delete the others*/
t_lexer	*min_here_set_file(t_lexer *token, char *path)
{
	t_lexer	*file;
	char	*old;

	file = token;
	old = token->value;
	token->key = l_word;
	token->value = path;
	min_free(&old);
	if (file->next && !min_token_is_word(file->key))
		file = file->next;
	ft_space(&file);
	ft_word(&file, token);
	token->next = file;
	if (file)
		file->prev = token;
	return (token);
}
