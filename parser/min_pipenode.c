/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_pipenode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:23:46 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/07 14:56:58 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"
static t_ast *ft_init_pipenode(t_ast *left, char first)
{
	t_ast   *pipe;

	pipe = (t_ast *)malloc(sizeof(t_ast));
	if (!pipe)
		return (NULL);
	ft_bzero(pipe, sizeof(t_ast));
	pipe->key = pipenode;
	pipe->node.pipe = (t_pipenode *)malloc(sizeof(t_pipenode));
	if (!pipe->node.pipe)
		return (NULL);
	ft_bzero(pipe->node.pipe, sizeof(t_pipenode));
	if (first)
	{
		pipe->node.pipe->left = left;
		if (pipe->node.pipe->left->key == subnode)
			pipe->node.pipe->left->node.sub->up = pipe;	
		else 
			pipe->node.pipe->left->node.job->up = pipe;
	}
	return (pipe);
}


/*
min_pipenode	--> 1. check if parse_error
               	--> 2. move upwards to last postition to create new pipeenode
                --> 3. if first pipenode create pipenode and linked in ast and prev in left tree
                --> 4. add new routenode in pipenode list
                return next token and clean total ast if any malloc failed or parse error.



*/



t_lexer *min_pipenode(t_lexer *token, t_ast **ast)
{
	t_ast	**left;
	t_ast	*oldpipe;
	
	if (!(*ast) || (*ast)->key == routenode)
		min_parser_error(ast, token);
	else
	{
		left = ast;
		if ((*ast)->key == jobnode)
            		*ast = (*ast)->node.job->up;
        	else if ((*ast)->key == subnode)
            		*ast = (*ast)->node.sub->up;
		if (!(*ast) || (*ast)->key == subnode)
        	{       
			*ast = ft_init_pipenode(*left, 1);
			if (!(*ast))
				min_parser_malloc_fail(left);
		}
		else
		{      
			oldpipe = *ast; 
                       	*ast = (*ast)->node.pipe->next;
                        *ast = ft_init_pipenode(*left, 0);
			if (!(*ast))
				min_parser_malloc_fail(left);
			else
                        	(*ast)->node.pipe->prev = oldpipe;
		}
	}
        return (token->next);
}		
