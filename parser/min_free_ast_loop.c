/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_free_ast_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:20:31 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/23 16:28:12 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_subnode(t_ast *ast)
{
	min_free_ast_loop(ast->u_no.sub->down);
	free(ast->u_no.sub);
	free(ast);
}

static void	ft_free_pipenode(t_ast *ast)
{
	while (ast->u_no.pipe)
	{
		min_free_ast_loop(ast->u_no.pipe->down);
		if (ast->u_no.pipe->next)
			ast = ast->u_no.pipe->next;
		else
			break ;
	}
	while (ast->u_no.pipe->prev)
	{
		ast = ast->u_no.pipe->prev;
		free(ast->u_no.pipe->next->u_no.pipe);
		free(ast->u_no.pipe->next);
	}
	free(ast->u_no.pipe);
	free(ast);
	ast = NULL;
}

static void	ft_free_routenode(t_ast *ast)
{
	min_free_ast_loop(ast->u_no.route->down);
	min_free_ast_loop(ast->u_no.route->next);
	free(ast->u_no.route);
	free (ast);
	ast = NULL;
}

static void	ft_free_jobnode(t_ast *ast)
{
	free(ast->u_no.job);
	free(ast);
}

void	min_free_ast_loop(t_ast *ast)
{
	if (!ast)
		return ;
	else if (ast->key == routenode)
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
	else if (ast->key == jobnode)
	{
		ft_free_jobnode(ast);
	}
}
