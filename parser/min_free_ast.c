/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_free_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:39:31 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/02 12:07:12 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/05/11 14:45:29 by jstrotbe         ###   ########.fr       */
/*   Updated: 2023/05/11 09:51:34 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_ast(t_ast *ast);

static void	ft_free_subnode(t_ast *ast)
{
	ft_free_ast(ast->node.sub->down);
//	ast->node.sub->down = NULL;
	free(ast->node.sub);
//	ast->node.sub = NULL;
	ast->node.sub->down = NULL;
//	printf("in sub[ %p ]\n", ast);
	free(ast);
}
/*
static void ft_free_pipenode(t_ast *ast)
{
	while((*ast)->node.pipe)
	{
		ft_free_ast(ast)->node.pipe->down);
		(*ast)->node.pipe->down = NULL;
		if ((*ast)->node.pipe->next)
			*ast = (*ast)->node.pipe->next;
 		else
			break;
	}
	while ((*ast)->node.pipe)
	{
		if ((*ast)->node.pipe->prev)
		{
			*ast = (*ast)->node.pipe->prev;
			free((*ast)->node.pipe->next);
			(*ast)->node.pipe->next = NULL;	
		}
		else
			break;
	}
	free (*ast);
	*ast = NULL;
}

static void ft_free_routenode(t_ast **ast)
{
    while((*ast)->node.route)
    {
        ft_free_ast(&(*ast)->node.route->down);
        (*ast)->node.route->down = NULL;
        if ((*ast)->node.route->next)
            *ast = (*ast)->node.route->next;
        else
            break;
    }
    while ((*ast)->node.route)
    {
        if ((*ast)->node.route->prev)
        {
            *ast = (*ast)->node.route->prev;
            free((*ast)->node.route->next);
            (*ast)->node.route->next = NULL;
        }
        else
            break;
    }
    free (*ast);
    *ast = NULL;
	
}


*/

static void	ft_free_jobnode(t_ast *ast)
{
	t_ast	*temp;

	temp = ast;
	//printf("in job.job[ %p ]\n", temp->node.job);
	free(temp->node.job);
	temp->node.job = NULL;
	//printf("in job[ %p ]\n", temp);
	free(temp);
	temp = NULL;
}

void	ft_free_ast(t_ast *ast)
{	
/*	
	if (ast->key == routenode)
    {
        return (ft_free_routenode(ast));
    }
    if (ast->key == pipenode)
    {
      return (ft_free_pipenode(ast));
    }*/
	if (ast->key == subnode)
	{
		//printf("sub\n");
		//printf("start sub[ %p ]\n", ast);
		ft_free_subnode(ast);
		//printf("end sub[ %p ]\n", ast);
	}
	if (ast->key == jobnode)
	{
		//printf("job\n");
		//printf("start job[ %p ]\n", ast);
		ft_free_jobnode(ast);
		//printf("end job[ %p ]\n", ast);
	}
}

void	min_free_ast(t_ast **ast)
{
	if (!*ast)
		return;
	min_bring_ast_to_beginning(ast);
	//printf("start ast[ %p ]\n", *ast);
	ft_free_ast(*ast);
	*ast = NULL;
}
