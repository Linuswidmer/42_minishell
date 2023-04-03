/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:59:26 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/03 18:08:26 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static int	ft_token_is_JOBNODE(t_lexertype key)
{
	if (min_is_IO(key) || min_is_WORD(key))
		return (1);
	else
		return (0);	 
}

static int	ft_token_is_PIPENODE(t_lexertype key)
{
	if (key == PIPE)
		return (1);
	else 
		return(0);		
}

static int	ft_token_is_ROUTENODE(t_lexertype key)
{
	if (min_is_PARA(key) || min_is_ROUTE(key))
		return (1);
	else
		return (0);
}

static void ft_bring_AST_to_beginning(t_AST **ast)
{
	int a;

	a = 1;
	while (a)
	{
		if ((*ast)->key == JOBNODE)
		{
			if (!(*ast)->NODE.job->up)
				a = 0;
			else
				*ast = (*ast)->NODE.job->up;			
		}

		/*	
		else if ((*ast)->key == PIPENODE)
		
		else if ((*ast)->key == ROUTENODE)
 
		if ((*ast)->key == JOBNODE && !(*ast)->NODE.job->up)
			a = 0;
		else if (*ast->up)
			*ast = *ast->up;
		else if (!*ast->last && !*ast->up)
			a = 0;		
		else if (*ast->last)
			*ast = *ast->last;*/
	}
}

/* PARSER MAIN*/
void	*min_parser(t_lexer *token)
{
	t_AST *ast;

	while (token)
	{
		if (ft_token_is_JOBNODE(token->key))
			token =	min_JOBENODE(token, &ast);	
		else if (ft_token_is_PIPENODE(token->key))
			token = min_PIPENODE(token, &ast);
		else if (ft_token_is_ROUTENODE(token->key))			
			token = min_ROUTENODE(token, &ast);	
	}
	ft_bring_AST_to_beginning(&ast);
	return (ast);
}
