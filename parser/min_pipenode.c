/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_pipenode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:23:46 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/23 18:00:05 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_ast	*ft_init_pipenode(void)
{
	t_ast	*pipe;

	pipe = (t_ast *)malloc(sizeof(t_ast));
	if (!pipe)
		return (NULL);
	ft_bzero(pipe, sizeof(t_ast));
	pipe->key = pipenode;
	pipe->node.pipe = (t_pipenode *)malloc(sizeof(t_pipenode));
	if (!pipe->node.pipe)
		return (NULL);
	ft_bzero(pipe->node.pipe, sizeof(t_pipenode));
	return (pipe);
}

static void	ft_route_pipe(t_ast **ast, t_ast **temp, t_ast **new)
{
	*new = ft_init_pipenode();
	if (!*new)
		min_parser_malloc_fail(ast);
	else
	{
		if (*ast && (*ast)->key == subnode)
			(*ast)->node.sub->down = *new;
		if (*ast && (*ast)->key == routenode)
			(*ast)->node.route->down = *new;
	}
	(*new)->node.pipe->down = *temp;
	if ((*temp)->key == jobnode)
	{
		(*new)->node.pipe->up = (*temp)->node.job->up;
		(*temp)->node.job->up = *new;
	}
	if ((*temp)->key == subnode)
	{
		(*new)->node.pipe->up = (*temp)->node.sub->up;
		(*temp)->node.sub->up = *new;
	}
	*ast = *new;
}

static void	ft_norm(t_ast **ast, t_ast **temp, t_ast **new)
{
	if (!*new)
		min_parser_malloc_fail(ast);
	else
	{
		(*ast)->node.pipe->next = *new;
		(*new)->node.pipe->prev = *temp;
		*ast = *new;
	}
}

/*
min_pipenode	
--> 1. check if parse_error
--> 2. move upwards to last postition to create new pipenode
--> 3. if first pipenode create pipenode and linked in ast and prev in left tree
--> 4. add new routenode in pipenode list
return next token and clean total ast if any malloc failed or parse error.
*/

t_lexer	*min_pipenode(t_lexer *token, t_ast **ast)
{
	t_ast	*temp;
	t_ast	*new;

	if (!(*ast) || min_is_last_token(token) || (*ast)->key == routenode 
		|| (*ast)->key == pipenode)
		min_parser_error(ast, token->key, NULL);
	else
	{
		temp = *ast;
		if ((*ast)->key == jobnode)
			*ast = (*ast)->node.job->up;
		else if ((*ast)->key == subnode)
			*ast = (*ast)->node.sub->up;
		if (!*ast || (*ast)->key == subnode || (*ast)->key == routenode)
			ft_route_pipe(ast, &temp, &new);
		temp = *ast;
		new = ft_init_pipenode();
		ft_norm(ast, &temp, &new);
	}
	return (token->next);
}
