/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:59:26 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/07/05 15:09:44 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_token_is_jobnode(t_lexertype key)
{
	if (min_token_is_io(key) || min_token_is_word(key))
		return (1);
	else
		return (0);
}

static int	ft_token_is_pipenode(t_lexertype key)
{
	if (key == l_pipe)
		return (1);
	else
		return (0);
}

static int	ft_token_is_routenode(t_lexertype key)
{
	return (min_token_is_route(key));
}

static int	ft_token_is_subnode(t_lexertype key)
{
	return (min_token_is_para(key));
}

/* 
PARSER MAIN	--> check each token from lexer
		--> create the right node
	return a full ast from the first node if something goes wrong 
	at the nodes it will return NULL
*/
t_ast	*min_parser(t_lexer *token)
{
	t_ast	*ast;

	ast = NULL;
	if (g_status == 130)
		g_status = 17;
	while (token && g_status != 130)
	{
		while (token && token->key == l_space)
			token = token->next;
		if (token && ft_token_is_jobnode(token->key))
			token = min_jobnode(token, &ast);
		else if (token && ft_token_is_pipenode(token->key))
			token = min_pipenode(token, &ast);
		else if (token && ft_token_is_routenode(token->key))
			token = min_routenode(token, &ast);
		else if (token && ft_token_is_subnode(token->key))
			token = min_subnode(token, &ast);
		if (!ast)
			break ;
	}
	min_bring_ast_to_beginning(&ast);
	if (_DEBUG)
		min_print_ast(ast);
	if (g_status == 17)
		g_status = 130;
	return (ast);
}
