/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_routenode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:43:03 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/05 20:32:32 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* route parse error */



#include "parser.h"
t_ast	*ft_close_para(t_ast *ast)
{
		if (





t_lexer	*min_routenode(t_lexer *token, t_ast **ast)
{
	if (min_token_is_para == 2)
		*ast = ft_close_para(*ast);		
	else if (min_token_is_para == 1)

	else
			
	return (token->next);
}		
