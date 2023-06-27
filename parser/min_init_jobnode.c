/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_init_jobnode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:12:34 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/23 17:32:34 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_ast	*min_init_jobnode(t_lexer *token)
{
	t_ast	*job;

	job = (t_ast *)malloc(sizeof(t_ast));
	if (!job)
		return (NULL);
	ft_bzero(job, sizeof(t_ast));
	job->key = jobnode;
	job->u_no.job = (t_jobnode *)malloc(sizeof(t_jobnode));
	if (!job->u_no.job)
		return (NULL);
	ft_bzero(job->u_no.job, sizeof(t_jobnode));
	job->u_no.job->start = token;
	return (job);
}
