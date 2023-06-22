/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_free_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:39:31 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/21 16:22:25 by jstrotbe         ###   ########.fr       */
/*   Updated: 2023/05/11 14:45:29 by jstrotbe         ###   ########.fr       */
/*   Updated: 2023/05/11 09:51:34 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static void	ft_free_subnode(t_ast *ast)
{
	min_free_ast_loop(ast->node.sub->down);
	free(ast->node.sub);
	free(ast);
}

static void ft_free_pipenode(t_ast *ast)
{
	while(ast->node.pipe)
	{
		min_free_ast_loop(ast->node.pipe->down);
		if (ast->node.pipe->next)
			ast = ast->node.pipe->next;
 		else
			break;
	}
	while (ast->node.pipe->prev)
	{
			ast = ast->node.pipe->prev;
			free(ast->node.pipe->next->node.pipe);
			free(ast->node.pipe->next);
	}
	free(ast->node.pipe);
	free (ast);
	ast = NULL;
}

static void ft_free_routenode(t_ast *ast)
{
    while(ast->node.route)
    {
        min_free_ast_loop(ast->node.route->down);
        if (ast->node.route->next)
            ast = ast->node.route->next;
        else
            break;
    }
    while (ast->node.route->prev)
    {
            ast = ast->node.route->prev;
			free(ast->node.route->next->node.pipe);
            free(ast->node.route->next);
    }
	free(ast->node.route);
    free (ast);
}

static void	ft_free_jobnode(t_ast *ast)
{
	free(ast->node.job);
	free(ast);
}

void	min_free_ast_loop(t_ast *ast)
{	
	
	if (ast->key == routenode)
    {
        return (ft_free_routenode(ast));
    }
    else if (ast->key == pipenode)
    {
      return (ft_free_pipenode(ast));
    }
	else if (ast->key == subnode)
	{
		ft_free_subnode(ast);
	}
	else if(ast->key == jobnode)
	{
		ft_free_jobnode(ast);
	}
}
*/
void	min_free_ast(t_ast **ast)
{
	if (!*ast)
		return;
	min_bring_ast_to_beginning(ast);
	min_free_ast_loop(*ast);
	*ast = NULL;
}
