/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_routenode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:43:03 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/07 15:16:32 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static t_ast *ft_move_and_store_prev(t_ast *ast, t_ast **prev)
{
	*prev = ast;
	 if (ast->key == jobnode)
                ast = ast->node.job->up;
        else if (ast->key == subnode)    
                ast = ast->node.sub->up;
        else if (ast->key == pipenode)
		ast = ast->node.pipe->up;
	return (ast);
}

static t_ast	*ft_init_routenode(void) 
{
	t_ast *route;

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

static t_ast *ft_set_routenode(t_ast **ast, t_ast *down, t_lexer *token)
{
	t_ast **temp;
	
	temp = ast;
	*ast = ft_init_routenode();
	if (!(*ast))
	{
		min_parser_malloc_fail(temp);
		return (*ast);
	}
	if (!token)
	{
		(*ast)->node.route->up = *temp;
		if (*temp)
			(*temp)->node.sub->down = *ast;
		(*ast)->node.route->down = down;
	}
	else
	{
		(*ast)->node.route->prev = *temp;
		(*temp)->node.route->next = *ast;
		(*temp)->node.route->rvalue = token->value;	
	}
	return (*ast);
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

	t_ast	*prev;
	
	if ((*ast)->key == pipenode || (*ast)->key == routenode)
		min_parser_error(ast, token);
	else
	{
		*ast = ft_move_and_store_prev(*ast, &prev);
		if ( *ast && (*ast)->key == pipenode)
		{
			while ((*ast)->node.pipe->prev)
				*ast = (*ast)->node.pipe->prev;
			*ast = ft_move_and_store_prev(*ast, &prev);
		}
		if (!(*ast) || (*ast)->key == subnode)
			*ast = ft_set_routenode( ast, prev, NULL);
		if ((*ast))
			*ast = ft_set_routenode(ast, NULL, token);
	}
	return (token->next);
}		
