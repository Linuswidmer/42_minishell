/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_set_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:32:48 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/17 14:22:00 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "expander.h"



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





ft_set_io_in(t_lexer *token, t_expandjob **job, t_dict *dict)
{
    t_ionode    *end;

    if (!(*job)->in)
        {
            job->in = ft_init_io(token);
            end = job->in;
        }
    else
        {
            end = min_last_ionode(job->in);
            end->next= ft_init_io(token);
            end = end->next;
        }
    if (end)
        token = min_set_file_io(&end, token->next);
    if (!end)
        min_expander_malloc_fail(job);
    return (token)
}

ft_set_io_out(t_lexer *token, t_expandjob **job, t_dict *dict)
{
    t_ionode    *end;

    if (!(*job)->out)
        {
            job->out = ft_init_io(token);
            end = job->out;
        }
    else
        {
            end = min_last_ionode(job->out);
            end->next= ft_init_io(token);
            end = end->next;
        }
    token = min_set_file_io(end);
    if(!end)
        min_expander_malloc_fail(job);
    return (token);
}






t_lexer *min_set_io(t_lexer *token, t_expandjob **job, t_dict *dict)
{
    if(min_token_is_io(astjob->token->key) < 3 )
        token = ft_set_io_in(token, &job, dict);
    else
        token = ft_set_io_out(token, &job, dict);
    return (token);
}
