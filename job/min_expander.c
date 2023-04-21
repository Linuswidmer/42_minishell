/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:34:53 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/21 14:11:31 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_expandjob *min_expander(t_lexer *token, t_dict *dict, t_lexer *end)
{
	t_expandjob *job;
	
	/* init job*/
		
	job = (t_expandjob *)malloc(sizeof(t_expandjob));
	if (!job)
		return (NULL);
	ft_bzero(job, sizeof(t_expandjob));
	
	/* token to job */
	while (token && token != end && job)
	{
		if (min_token_is_io(token->key))
			token = min_set_io(token, &job, dict);
		else if (token->key == l_space)
			token = token->next; 		 
		else
			token =  min_set_cmd(token, &job, dict);
	}
	return (job);
}

