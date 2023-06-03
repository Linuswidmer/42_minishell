/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_subnode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:26:53 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/25 11:41:03 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*ft_navigate_to_next_sub(t_ast *ast, char first)
{
	if (ast)
	{
		if (ast->key == jobnode)
			ast = ast->node.job->up;
		else if (ast->key == subnode && first)
			ast = ast->node.sub->up;
		else if (ast->key == pipenode && ast->node.pipe->prev)
			ast = ast->node.pipe->prev;
		else if (ast->key == pipenode && !ast->node.pipe->prev)
			ast = ast->node.pipe->up;
		else if (ast->key == routenode && ast->node.route->prev)
			ast = ast->node.route->prev;
		else if (ast->key == routenode && !ast->node.route->prev)
			ast = ast->node.route->up;
		else if (ast->key == subnode && !first)
			return (ast);
		return (ft_navigate_to_next_sub(ast, 0));
	}
	return (ast);
}

static t_ast	*ft_close_para(t_ast **ast, t_lexer *token)
{
	t_ast	**temp;

	if (!*ast || (*ast)->key == pipenode || (*ast)->key == routenode)
		min_parser_error(ast, token->key, NULL);
	else
	{
		temp = ast;
		*ast = ft_navigate_to_next_sub(*ast, 1);
		if (!*ast)
			min_parser_error(temp, token->key, NULL);
	}
	return (*ast);
}

static t_ast	*ft_init_subnode(void)
{
	t_ast	*sub;

	sub = (t_ast *)malloc(sizeof(t_ast));
	if (!sub)
		return (NULL);
	ft_bzero(sub, sizeof(t_ast));
	sub->key = subnode;
	sub->node.sub = (t_subnode *)malloc(sizeof(t_subnode));
	if (!sub->node.sub)
		return (NULL);
	ft_bzero(sub->node.sub, sizeof(t_subnode));
	return (sub);
}

static int	ft_last_is_paraclose(t_lexer *token)
{
	token = token->prev;
	while (token && (token->key == l_space))
		token = token->prev;
	if (token && token->key == l_paraclose)
		return (1);
	else
		return (0);
}

static t_ast	*ft_open_para(t_ast **ast, t_lexer *token)
{
	t_ast	*new;

	if (*ast)
	{
		if ((*ast)->key == jobnode || ((*ast)->key == subnode
				&& ft_last_is_paraclose(token)))
		{
			min_parser_error(ast, token->key, NULL);
			return (NULL);
		}
	}	
	new = ft_init_subnode();
	if (!new)
		min_parser_malloc_fail(ast);
	else
		new->node.sub->up = *ast;
	if (*ast && (*ast)->key == subnode)
		(*ast)->node.sub->down = new;
	if (*ast && (*ast)->key == pipenode)
		(*ast)->node.pipe->down = new;
	if (*ast && (*ast)->key == routenode)
		(*ast)->node.route->down = new;
	*ast = new;
	return (*ast);
}

/*
min_subnode	
		--> 1. if para_open -> new subnode get createtd;
		--> 2. if para_closed 	-> ceck parse error 
					-> move up to next subshell
		 return next token and clean total ast if any malloc failed or parse error.
*/
t_lexer	*min_subnode(t_lexer *token, t_ast **ast)
{
	if (min_token_is_para(token->key) == 1)
	{	
		if (!min_is_last_token(token))
			*ast = ft_open_para(ast, token);
		else
			min_parser_error(ast, token->key, NULL);
	}
	else
		*ast = ft_close_para(ast, token);
	return (token->next);
}
