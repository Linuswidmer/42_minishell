/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:02:20 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/10 15:52:35 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include <stdlib.h>
# include "libft.h"

# ifndef _DEBUG1	
#  define _DEBUG1 1	
# endif

# ifndef _DEBUG    
#  define _DEBUG 1 
# endif


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
	t_ast *up;
    t_ast *down;
};

struct s_routenode
{
	t_lexertype rvalue;
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
	t_ast *down;	
	
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
	t_lexertype value;
	char	*arg;
	t_cmdnode *next;	
};

struct s_ionode
{
	t_lexertype value;
	char *file;
	t_ionode *next;
};

struct s_ast
{
    e_type key;
    union
    {
        t_pipenode	*pipe;
        t_jobnode	*job;
		t_routenode	*route;
		t_subnode	*sub;
    }node;
};


/* FUNCTIONS */

t_ast	*min_parser(t_lexer *token); /* x */
void	min_parser_error(t_ast **ast, t_lexer *token);
void    min_parser_malloc_fail(t_ast **ast);
void	min_bring_ast_to_beginning(t_ast **ast);
void    min_free_ast(t_ast **ast);



/* ROUTE */
t_lexer *min_routenode(t_lexer *token,t_ast **ast);
int     min_token_is_route(t_lexertype key);

/* SUB */
int		min_token_is_para(t_lexertype key);
t_lexer *min_subnode(t_lexer *token, t_ast **ast);


/* PIPE */
t_lexer *min_pipenode(t_lexer *token, t_ast **ast);

/* JOBNODE */
t_lexer	*min_jobnode(t_lexer *token, t_ast **ast);

/* IO */
t_lexer		*min_set_io(t_lexer *token, t_ast **ast);
int			min_token_is_io(t_lexertype key); /*x*/
int			min_token_is_io_in(t_lexertype key);
t_ionode	*min_last_ionode(t_ionode *node);
void		min_set_file_io(t_lexer *token, t_ast *ast);


/* cmd */
void    min_set_cmd(t_lexer *token, t_ast **ast);
t_cmdnode	*min_last_cmdnode(t_cmdnode *node);



/* WORD */
int     min_token_is_word(t_lexertype key);/*x*/
	
/* DEBUG */ 
void min_print_io(t_ionode *io);
void min_print_cmd (t_cmdnode *cmd);
void min_print_ast(t_ast *ast);
void    min_print_jobnode(t_jobnode *job);



#endif
