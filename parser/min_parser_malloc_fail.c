/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_parser_malloc_fail.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:02:31 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/10 14:44:41 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"





void	min_parser_malloc_fail(t_ast **ast)
{
	printf("MALLOC_FAIL");
	min_bring_ast_to_beginning(ast);
	min_free_ast(ast);	
}
