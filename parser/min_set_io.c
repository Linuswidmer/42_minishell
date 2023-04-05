/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_set_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:54:47 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/05 18:15:09 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"



static t_ionode *ft_init_io(t_lexer *token, t_ast *ast)
{
	t_ionode *node;
	node = (t_ionode *)malloc(sizeof(t_ionode));
	if (!node)
	{
		min_free_ast(ast);
		return (node);
	}
	ft_bzero(node, sizeof(t_ionode));
	node->value = token->value;
	return (node);
}


t_lexer *min_set_io(t_lexer *token, t_ast *ast)
{
    t_jobnode *job;
	t_ionode *end;

    job = ast->node.job
    if (min_token_is_io_in(token->key))
    {
        if (!job->in)
            job->in = ft_init_io(token, ast);
        else
		{
			end = min_last_ionode(job->in); 	
			end = ft_init_io(token, ast);
    	}
	}
    else
    {
		if (!job->out)
            job->out = ft_init_io(token, ast);
        else
        {
            end = min_last_ionode(job->out);
            end = ft_init_io(token, ast);
        }
    }
    return (token->next);
}

