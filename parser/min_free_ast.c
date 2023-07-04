/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_free_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:39:31 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/28 13:33:39 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/05/11 14:45:29 by jstrotbe         ###   ########.fr       */
/*   Updated: 2023/05/11 09:51:34 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	min_free_ast(t_ast **ast)
{
	if (!ast)
		return ;
	min_bring_ast_to_beginning(ast);
	min_free_ast_loop(*ast);
	*ast = NULL;
}
