/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:46:27 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/01 18:53:16 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jstr.h"

void *last_node(void *node)
{
	while (node->next)
		node = node->next;
	return (node);
} 


void	init_ROUTENODE(t_ROUTENODE **ast)
{
	t_ROUTENODE *end;
		
	if (!*ast)
	{
		*ast = (t_ROUTENODE *)malloc(sizeof(t_ROUTENODE));		 	
		if (!*ast)
			min_free_ast(**ast);
		end = *ast;		
	}
	else
	{
		end = last_node(*ast); 
		end->next = (t_ROUTENODE *)malloc(sizeof(t_ROUTENODE));
		if (!end->next)
            min_free_ast(**ast);
		end = end->next;
	}
	ft_bzero(end, sizeof(t_ROUTENODE));
	end->under = (t_JOBNODE *)malloc(sizeof(t_JOBNODE));
	if (!end->under)
            min_free_ast(**ast);
	ft_bzero(end->under, sizeof(t_JOBNODE)); 
}


void	parser(t_lexer *data, t_ROUTENODE **ast)
{
	
	init_ROUTENODE(ast);	
	
	while (data)
	{
		if (data->key == DQUOTE || data->key == QUOTE)	
			data = data->next;
		else
			


















int	main(void)
{





		
}




