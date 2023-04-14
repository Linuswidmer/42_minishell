/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_set_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:54:47 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/12 16:21:21 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"



static t_ionode *ft_init_io(t_lexer *token)
{
	t_ionode *io;
	io = (t_ionode *)malloc(sizeof(t_ionode));
	if (!io)
		return (NULL);
	ft_bzero(io, sizeof(t_ionode));
	io->value = token->key;
	return (io);
}


t_lexer *min_set_io(t_lexer *token, t_ast **ast)
{
    t_jobnode	*job;
	t_ionode 	*end;

    job = (*ast)->node.job;
    if (min_token_is_io_in(token->key))
    {
        if (!job->in)
		{
            job->in = ft_init_io(token);
			if (!job->in)
				 min_parser_malloc_fail(ast);
		}
        else
		{
			end = min_last_ionode(job->in); 	
			end->next= ft_init_io(token);
			if (!end->next)
				min_parser_malloc_fail(ast);
    	}
	}
    else
    {
		if (!job->out)
		{
            job->out = ft_init_io(token);
			if (!job->out)
				min_parser_malloc_fail(ast);
		}	
        else
        {
            end = min_last_ionode(job->out);
            end->next = ft_init_io(token);
			if (!end->next)
                min_parser_malloc_fail(ast);
        }
    }
    return (token->next);
}

