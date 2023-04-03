/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:02:20 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/03 18:08:34 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

# define _T NODE.job->up

/* AST struct */
typedef struct s_AST		t_AST;
typedef struct s_PIPENODE	t_PIPENODE;
typedef struct s_JOBNODE 	t_JOBNODE;
typedef struct s_CMDNODE 	t_CMDNODE;
typedef struct s_IONODE		t_IONODE;
typedef struct s_ROUTENODE 	t_ROUTENODE;

typedef enum e_type
{
	ROUTENODE,
	PIPENODE,
	JOBNODE,
	CMDNODE,
	IONODE,
} e_type;

/*
struct s_AST
{
	e_type key;
	union
	{
		t_PIPENODE pipe;
		t_JOBNODE job;
		t_ROUTENODE route;
	}NODE;
};*/

struct s_ROUTENODE
{
	e_type key;
	char *rvalue;
	t_AST *up;
	t_AST *down;
	t_AST *next;
	t_AST *last;
};


struct s_PIPENODE
{
	e_type key;
	t_AST *next;
	t_AST *last;
	t_AST *up;
	t_AST *left_job;
	t_AST *right_job;
};

struct s_JOBNODE
{
	e_type key;
	t_AST *up;
	t_CMDNODE *cmd;
	t_IONODE *in;
	t_IONODE *out;
};

struct s_CMDNODE
{
	e_type key;
	char **args;
};

struct s_IONODE
{
	e_type key;
	char *value;
	char **files;
	t_IONODE *next_ionode;
};

struct s_AST
{
    e_type key;
    union
    {
        t_PIPENODE *pipe;
        t_JOBNODE *job;
        t_ROUTENODE *route;
    }NODE;
};


/* FUNCTIONS */

void    *min_parser(t_lexer *token);

/* ROUTE */
t_lexer *min_ROUTENODE(t_lexer *token,t_AST **ast);
int	min_is_PARA(t_lexertype key);
int     min_is_ROUTE(t_lexertype key);



/* PIPE */
t_lexer *min_PIPENODE(t_lexer *token, t_AST **ast);

/* JOBNODE */
t_lexer	*min_JOBENODE(t_lexer *token, t_AST **ast);

/* IO */
int     min_is_IO(t_lexertype key);

/* WORD */
int     min_is_WORD(t_lexertype key);
	
#endif
