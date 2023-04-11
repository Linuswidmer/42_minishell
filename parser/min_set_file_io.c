/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_set_file_io.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:59:53 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/07 18:43:44 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"



void	min_set_file_io(t_lexer *token, t_ast *ast)
{	
	t_ionode *end;
	if (min_token_is_io_in(token->prev->key))
	{
		end = min_last_ionode(ast->node.job->in);
	}
	else
	{
		end = min_last_ionode(ast->node.job->out);
	}	
	end->file = token->value;
}
