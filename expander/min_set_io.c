/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_set_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:32:48 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/26 12:08:51 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"



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


ft_set_io(t_lexer *token, t_expandjob **job, t_dict *dict)
{
    t_ionode    *end;

    if (!(*job)->io)
        {
            job->io = ft_init_io(token);
            end = job->io;
        }
    else
        {
            end = min_last_ionode(job->out);
            end->next= ft_init_io(token);
            end = end->next;
        }
    token = min_set_file_io(&end, token->next, dict);
    if(!end)
        min_expander_malloc_fail(job);
    return (token);
}


t_lexer *min_set_io(t_lexer *token, t_expandjob **job, t_dict *dict)
{
    return (ft_set_io(token, job, dict));
}
