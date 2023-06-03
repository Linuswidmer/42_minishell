/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_parser_malloc_fail.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:02:31 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/25 11:24:57 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	min_parser_malloc_fail(t_ast **ast)
{
	printf("MALLOC_FAIL");
	min_bring_ast_to_beginning(ast);
	min_free_ast(ast);
}
