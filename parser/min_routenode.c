/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_routenode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:43:03 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/05 21:13:31 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* route parse error */



#include "parser.h"
t_ast	*ft_close_para(t_ast *ast, char first)
{		
			
		if (!ast)
			return (NULL);
		if (ast->key == jobnode)
			ast = ast->node.job->up;
		else if (ast->key == pipe && ast->node.pipe->prev)
			ast = ast->node.pipe->prev;
		else if (ast->key == pipe && !ast->node.pipe->prev)
			ast = ast->node.pipe->up;
		/* check if && route*/
		else if (ast->key == route && ast->node.route->prev
			ast = ast->node.route->prev;
		else if (ast->key == route && ast->node.route->rvalue is && || ;)
			 ast = 	ast->node.route->up;
		else if (ast->key == route && ast->node.route->rvalue is () && !first)
			return (ast);
		else if (ast->key == route && ast->node.route->rvalue is () && first)
			ast =  ast->node.route->up;
		ft_close_para(ast, 0);
}

t_lexer	*min_routenode(t_lexer *token, t_ast **ast)
{
	if (min_token_is_para == 2)
		*ast = ft_close_para(*ast, 1);		
	else if (min_token_is_para == 1)

	else
			
	return (token->next);
}		
