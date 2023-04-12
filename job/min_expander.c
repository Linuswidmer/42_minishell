/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:34:53 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/12 16:38:22 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

ft_init_job()





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

char *ft_set_filename(t_lexer **token, t_dict *dict)
{
	char **values;

	values = min_dollar_asteriks_eval(token, dict);
	if (!values)
		return (NULL);
	if (ft_to_many_values(values))
	{
		ft_error_values(values)
		return (NULL);
	}
	return (values[0]);
}


t_lexer *ft_set_file_io(t_ionode **end, t_lexer *token, t_dict *dict)
{
	bool	space;
	char 	*value;	

	
	space = true;
	
	
	while (token && space && *end)
	{
		if (min_token_is_word(token->key && space))
		{
			space = false;
			value =  ft_set_filename(&token, dict);
		}
		else
			token = token->next; 
	}
	if (!value)
		ft_free_end(end);
	return (token)
}

	
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


t_lexer *ft_set_io(t_lexer *token, t_expandjob **job, t_dict *dict)
{
	if(min_token_is_io(astjob->token->key) < 3 )
		token = ft_set_io_in(token, &job, dict);
	else
		token = ft_set_io_out(token, &job, dict);	
	return (token); 
}


t_expandjob *min_expander(t_lexer *token, t_dict *dict)
{
	t_expandjob *job;
	
	/* init job*/
		
	job = (t_expandjob *)malloc(sizeof(t_expandjob));
	if (!job)
		return (NULL);
	ft_bzero(job, sizeof(t_expandjob));
	
	/* token to job */
	while (token || job)
	{
		if (min_token_is_io(astjob->token->key))
			token = ft_set_io(token, &job, dict); 		 
		else
			token =  min_set_cmd(token, &job, dict);
	}
	return (job);
}

