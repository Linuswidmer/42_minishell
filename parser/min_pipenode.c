/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_pipenode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:23:46 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/05 20:32:03 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"
static t_ast *ft_init_pipenode(t_ast *left, char first)
{
    t_ast   *pipe;
    pipe = (t_ast *)malloc(sizeof(t_ast));
    if (!pipe)
        min_free_ast(left);
    ft_bzero(pipe, sizeof(t_ast));
    pipe->key = pipenode;
    pipe->node.pipe = (t_pipenode *)malloc(sizeof(t_pipenode));
    if (!pipe->node.pipe)
        min_free_ast(left);
    ft_bzero(pipe->node.pipe, sizeof(t_pipenode));
	if (first)
	{
    	pipe->node.pipe->left = left;
		if (pipe->node.pipe->left->key == route)
			pipe->node.pipe->left.route->up = pipe;	
		else
			pipe->node.pipe->left.job->up = pipe;
	}
    return (pipe);
}






t_lexer *min_pipenode(t_lexer *token, t_ast **ast)
{
    t_ast	*temp;
	t_ast	*oldpipe;

    temp = *ast;
    if (*ast)
    {
        if ((*ast)->key == job)
            *ast = (*ast)->node.job->up;
        if ((*ast)->key == route)
            *ast = (*ast)->node.route->up;
    }
	if (*ast)
	{	
		if ((*ast)->key == pipe)
		{
			oldpipe = *ast;	
			*ast = (*ast)->node.pipe->next;
			*ast = t_init_pipenode(temp, 0);
			(*ast)->node.pipe->prev = oldpipe;
		}					
		else if ((*ast)->key == route)
			*ast = ft_init_pipenode(temp, 1);
	}
	else
		*ast = ft_init_pipenode(temp, 1);	
	return (token->next);
}		
