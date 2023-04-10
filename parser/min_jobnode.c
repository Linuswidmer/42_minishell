/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_jobnode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:31:01 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/10 14:33:34 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast *ft_init_jobnode()
{
	t_ast	*job;
	job = (t_ast *)malloc(sizeof(t_ast));
	if (!job)
		return (NULL);
	ft_bzero(job, sizeof(t_ast));
	job->key = jobnode;	
	job->node.job = (t_jobnode *)malloc(sizeof(t_jobnode)); 
	if (!job->node.job)
		return (NULL);	
	ft_bzero(job->node.job, sizeof(t_jobnode));
	return (job);
}

static t_lexer *ft_set_word(t_lexer *token, t_ast **ast)
{
	if (token->prev && min_token_is_io(token->prev->key))
		min_set_file_io(token, *ast);		
	else			 	
			min_set_cmd(token, ast);			
	return (token->next);
}
/*
min_jobnode 
        --> 1. if para_open -> new subnode get createtd;
        --> 2. if para_closed   -> ceck parse error 
                    -> move up to next subshell
         return next token and clean total ast if any malloc failed or parse error.
*/


t_lexer	*min_jobnode(t_lexer *token, t_ast **ast)
{
	t_ast *new;

	new = ft_init_jobnode();
	if (!new)
		min_parser_malloc_fail(ast);
	else		
		new->node.job->up = *ast;	
	if (*ast)
	{
		if ((*ast)->key == pipenode)
			(*ast)->node.pipe->down = new;				
		else if ((*ast)->key == routenode)
			(*ast)->node.route->down = new;
		else if ((*ast)->key == subnode)
			(*ast)->node.sub->down = new;
	}
	*ast = new;
	while (token && *ast)
	{
		if (min_token_is_io(token->key))
			token = min_set_io(token, ast);
		else if (min_token_is_word(token->key))
			token = ft_set_word(token, ast);
		else
			break;
	}
	return (token);
}
