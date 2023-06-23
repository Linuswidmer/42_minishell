/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_routenode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:43:03 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/23 18:40:33 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_ast	*ft_init_routenode(void)
{
	t_ast	*route;

	route = (t_ast *)malloc(sizeof(t_ast));
	if (!route)
		return (NULL);
	ft_bzero(route, sizeof(t_ast));
	route->key = routenode;
	route->node.route = (t_routenode *)malloc(sizeof(t_routenode));
	if (!route->node.route)
		return (NULL);
	ft_bzero(route->node.route, sizeof(t_routenode));
	return (route);
}

t_ast	*ft_find_brange(t_ast *ast, t_ast **temp)
{
	if (ast->key == jobnode)
	{
		if (ast->node.job->up && ast->node.job->up->key != subnode)
			ast = ast->node.job->up;
		else
			*temp = ast->node.job->up;
	}
	else if (ast->key == subnode)
	{
		if (ast->node.sub->up && ast->node.sub->up->key != subnode)
			ast = ast->node.sub->up;
		else
			*temp = ast->node.sub->up;
	}
	if (ast->key == pipenode)
	{
		while (ast->node.pipe->prev)
			ast = ast->node.pipe->prev;
		if (ast->node.pipe->up && ast->node.pipe->up->key != subnode)
			ast = ast->node.pipe->up;
		else
			*temp = ast->node.pipe->up;
	}
	return (ast);
}

static void	ft_route(t_ast **ast, t_ast **new, t_ast **temp)
{
	*new = ft_init_routenode();
	if (!*new)
		min_parser_malloc_fail(ast);
	else
	{
		(*new)->node.route->up = *temp;
		if (*temp)
			(*temp)->node.sub->down = *new;
		(*new)->node.route->down = *ast;
		if ((*ast)->key == jobnode)
			(*ast)->node.job->up = *new;
		if ((*ast)->key == pipenode)
			(*ast)->node.pipe->up = *new;
		if ((*ast)->key == subnode)
			(*ast)->node.sub->up = *new;
		*ast = *new;
	}
}

static void	ft_norm(t_ast **ast, t_ast **new, t_ast **temp, t_lexer *token)
{
	if (ast)
	{
		(*ast)->node.route->next = *new;
		(*ast)->node.route->rvalue = token->key;
		(*new)->node.route->prev = *temp;
	}
	*ast = *new;
}

/*    
min_routenode	--> 1. check if parse_error
		--> 2. move upwards to last postition to create new routenode
		--> 3. if first routenode create routenode and linked in ast (like pipe)
		--> 4. add new routenode in routenode list and store evaluations in old one.
		return next token and clean total ast if any malloc faiuled or parse error. 			
*/

t_lexer	*min_routenode(t_lexer *token, t_ast **ast)
{
	t_ast	*new;
	t_ast	*temp;

	temp = *ast;
	if (!(*ast) || min_is_last_token(token) || (*ast)->key == pipenode 
		|| (*ast)->key == routenode)
		min_parser_error(ast, token->key, NULL);
	else
	{
		*ast = ft_find_brange(*ast, &temp);
		if (!temp || temp->key == subnode)
			ft_route(ast, &new, &temp);
		temp = *ast;
		new = ft_init_routenode();
		if (!new)
			min_parser_malloc_fail(ast);
		else
			ft_norm(ast, &new, &temp, token);
	}
	return (token->next);
}
