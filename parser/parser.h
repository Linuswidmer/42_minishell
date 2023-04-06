/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:02:20 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/05 21:13:33 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include <stdlib.h>
# include "libft.h"

/* AST struct */
typedef struct s_ast		t_ast;
typedef struct s_pipenode	t_pipenode;
typedef struct s_jobnode 	t_jobnode;
typedef struct s_cmdnode 	t_cmdnode;
typedef struct s_ionode		t_ionode;
typedef struct s_routenode 	t_routenode;
typedef struct s_subnode	t_subnode;



typedef enum e_type
{
	routenode,
	pipenode,
	jobnode,
	subnode,
} e_type;

struct s_subnode
{
	e_type	key
	t_ast *up;
        t_ast *down;
}

struct s_routenode
{
	char *rvalue;
	t_ast *up;
	t_ast *down;
	t_ast *next;
	t_ast *prev;
};


struct s_pipenode
{
	t_ast *next;
	t_ast *prev;
	t_ast *up;
	t_ast *left_job;
	t_ast *right_job;
};

struct s_jobnode
{
	t_ast 		*up;
	t_cmdnode	*cmd;
	t_ionode 	*in;
	t_ionode 	*out;
};

struct s_cmdnode
{
	char	*arg;
	char **args;
	t_cmdnode *next;	
};

struct s_ionode
{
	char *value;
	char *file;
	t_ionode *next;
};

struct s_ast
{
    e_type key;
    union
    {
        t_pipenode *pipe;
        t_jobnode *job;
        t_routenode *route;
	t_subnode *sub;
    }node;
};


/* FUNCTIONS */

t_ast	*min_parser(t_lexer *token); /* x */

/* ROUTE */
t_lexer *min_routenode(t_lexer *token,t_ast **ast);
int		min_is_para(t_lexertype key);
int     min_is_route(t_lexertype key);



/* PIPE */
t_lexer *min_pipenode(t_lexer *token, t_ast **ast);

/* JOBNODE */
t_lexer	*min_jobnode(t_lexer *token, t_ast **ast);

/* IO */
int     min_token_is_io(t_lexertype key); /*x*/

/* WORD */
int     min_token_is_word(t_lexertype key);/*x*/
	
#endif
