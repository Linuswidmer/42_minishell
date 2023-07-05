/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_jobnode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:31:01 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/07/05 13:45:56 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static t_ast	*min_init_jobnode(t_lexer *token)
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
*/
static void	ft_link_jobnode_into_ast(t_ast **ast, t_ast *new)
{
	if ((*ast)->key == pipenode)
		(*ast)->u_no.pipe->down = new;
	else if ((*ast)->key == routenode)
		(*ast)->u_no.route->down = new;
	else if ((*ast)->key == subnode)
		(*ast)->u_no.sub->down = new;
}

static int	ft_check_subshell(t_lexer *token)
{
	token = token->prev;
	while (token && token->key == l_space)
		token = token->prev;
	if (token && token->key == l_paraclose)
		return (1);
	else
		return (0);
}

static int	ft_token_not_valid(t_lexer **token, t_ast **ast, char *io)
{
	if (min_token_is_io((*token)->key) == 2 && !*io)
	{
		if (min_heredoc(token, HEREDOC))
			return (min_heredoc_fail(ast));
	}
	else if (min_token_is_io((*token)->key))
	{
		if (!*io)
			*io = 1;
		else
			return (min_parser_error(ast, (*token)->key, NULL));
	}
	else if (min_token_is_word((*token)->key) && *io)
		*io = 0;
	if ((*token)->next || !*io)
		return (0);
	else
		return (min_parser_error(ast, (*token)->key, P_NEWLINE));
}

static t_lexer	*ft_find_last_token(t_lexer *token, t_ast **ast)
{
	char	io;

	io = 0;
	while (token && g_status != 130)
	{
		if (min_token_is_jobnode(token->key))
		{
			if (ft_token_not_valid(&token, ast, &io))
				break ;
			token = token->next;
		}
		else
		{
			if (io)
				min_parser_error(ast, token->key, NULL);
			break ;
		}
	}
	return (token);
}

/*
min_jobnode 
--> 1. create jobnode
--> 2. store beginning and last token 
return next token and clean total ast if any malloc failed or parse error.
*/

/* !!! to do check if  everythink is valid !!!! */
t_lexer	*min_jobnode(t_lexer *token, t_ast **ast)
{
	t_ast	*new;

	if (ft_check_subshell(token))
		token = min_add_io_to_sub(token, ast);
	else
	{
		new = min_init_jobnode(token);
		if (new)
		{
			new->u_no.job->up = *ast;
			if (*ast)
				ft_link_jobnode_into_ast(ast, new);
			*ast = new;
			token = ft_find_last_token(token, ast);
			if (*ast)
				(*ast)->u_no.job->last = token;
		}
		else
		{
			min_parser_malloc_fail(ast);
		}
	}
	return (token);
}
