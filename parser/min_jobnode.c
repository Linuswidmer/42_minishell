/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_jobnode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:31:01 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/04 20:45:58 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* check if *ast  -->  if *ast is pipe or route -> navigade and then create  */
/* t_ast *temp = *ast -> *ast = init_jobnode */
/* while (token)
{	if min_is_io(key)
		ft_io() 
	else if (min_is_word(key)
		ft_word()
	else
		break          
} */




static t_ast *ft_init_jobnode(t_ast *up)
{
	t_ast	*job;
	job = (t_ast *)malloc(sizeof(t_ast));
	if (!job)
		min_free_ast(up);
	ft_bzero(job, sizeof(t_ast));
	job->key = jobnode;	
	job->node.job = (t_jobnode *)malloc(sizeof(t_jobnode)); 
	if (!job->node.job)
		min_free_ast(up);	
	ft_bzero(job->node.job, sizeof(t_jobnode));
	job->node.job->up = up;
	return (job);
}

static t_lexer *ft_set_word(t_lexer *token, t_ast *ast)
{
	if (token->last && min_token_is_io(token->last->key))
		min_set_file_io(token, ast);		
	else			 	
		




}


t_lexer	*min_jobnode(t_lexer *token, t_ast **ast)
{
	t_ast *temp;

	temp = *ast;
	if (*ast)
	{
		if ((*ast)->key == pipe)
			*ast = (*ast)->node.pipe->right_job;				
		if ((*ast)->key == route)
			*ast = (*ast)->node.route->down;
	}
	*ast = ft_init_jobnode(temp);	
	while (*token)
	{
		if (min_token_is_io(token->key))
			token = min_set_io(token, *ast)
		else if (min_is_word(token->key))
			token = ft_set_word(token, *ast)
		else
			break;
	}
	return (token);
}
