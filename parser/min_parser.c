/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:59:26 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/05 20:31:43 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static int	ft_token_is_jobnode(t_lexertype key)
{
	if (min_token_is_io(key) || min_token_is_word(key))
		return (1);
	else
		return (0);	 
}

static int	ft_token_is_pipenode(t_lexertype key)
{
	if (key == PIPE)
		return (1);
	else 
		return(0);		
}

static int	ft_token_is_routenode(t_lexertype key)
{
	if (min_token_is_para(key) || min_token_is_route(key))
		return (1);
	else
		return (0);
}

static void ft_bring_ast_to_beginning(t_ast **ast)
{
	int a;

	a = 1;
	while (a)
	{
		if ((*ast)->key == jobnode)
		{
			if (!(*ast)->node.job->up)
				a = 0;
			else
				*ast = (*ast)->node.job->up;			
		}
		else if ((*ast)->key == pipenode)
		{
			if (!(*ast)->node.pipe->last && !(*ast)->node.pipe->up)
            	a = 0;      
			else if (!(*ast)->node.pipe->up) 
				*ast = (*ast)->node.pipe->last;
			else 
				*ast =  (*ast)->node.pipe->up;

		}
		else if ((*ast)->key == routenode)
		{
			if (!(*ast)->node.route->last && !(*ast)->node.route->up)
                a = 0;
            else if (!(*ast)->node.route->up)
                *ast = (*ast)->node.route->last;
            else
                *ast =  (*ast)->node.route->up;
 		}
	}
}

/* PARSER MAIN*/
t_ast	*min_parser(t_lexer *token)
{
	t_ast *ast;

	while (*token)
	{
		if (ft_token_is_jobnode(token->key))
			token =	min_jobnode(token, &ast);	
		else if (ft_token_is_pipenode(token->key))
			token = min_pipenode(token, &ast);
		else if (ft_token_is_routenode(token->key))			
			token = min_routenode(token, &ast);	
	}
	ft_bring_ast_to_beginning(&ast);
	return (ast);
}


