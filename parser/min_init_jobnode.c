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
	job->node.job = (t_jobnode *)malloc(sizeof(t_jobnode));
	if (!job->node.job)
		return (NULL);
	ft_bzero(job->node.job, sizeof(t_jobnode));
	job->node.job->start = token;
	return (job);
}
