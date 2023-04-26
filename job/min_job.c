
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_job.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:36:54 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/25 12:33:21 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ?????? */ 
#include "expander.h"


/*  */
static int ft_is_buildin(char *cmd, t_build **build)
{
	while (*build && cmd)
	{
		if (!ft_strncmp(*build, cmd, ft_strlen(cmd))
			return (1);
		(*build)++;
	}
	return (0);
}	


/*   */
static int ft_cmd_is_buildin(t_jobnode *job, t_dict *dict, t_build **build)
{
	t_lexer *token;
	char	in;
	char	**cmd;
	
	in = 0;
	token = job->start;
	while (token && token != job->end)
	{
		if (min_token_is_word(token->key) && !in)
			break;
		else if (min_token_is_word(token->key) && in)
		{
			while(token && min_token_is_word(token->key))
				token = token->next;
			in = 0;
		}
		else if (min_token_is_io(token->key))
		{
			token = token->next;
			in = 1;
		}
	}
	cmd = min_word_eval(&token, dict);
	return ( ft_is_buildin(cmd[0], build); 
	
	
}

/*      */

static int		ft_job(t_jobnode *job, t_dict *dict, t_build **build)
{
	if (ft_cmd_is_buildin(job, dict ,build))
		return (min_buildin_cmd(job, dict, build));
	else
		return (min_common_cmd(job ,dict));
}		

/*    */
int 	min_job(t_ast *ast, t_dict *dict, t_build **build  )
{
	return (ft_job(ast->node.job, dict, build));
}
