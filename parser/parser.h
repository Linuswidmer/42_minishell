/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jstr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:29:48 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/01 18:53:14 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


typedef struct s_PIPENODE t_PIPENODE;
typedef struct s_JOBNODE t_JOBNODE;
typedef struct s_CMDNODE t_CMDNODE;
typedef struct s_IONODE t_IONODE;
typedef struct s_ROUTENODE t_ROUTENODE;


typedef enum 
{
	DQUOTE,
	QUOTE,
	WORD,
	ASTERIX,
	PARAOPEN,
	PARACLOSE,
	HEREDOC,
	APPEND,
	IN,
	OUT,
	AND,
	OR,
	SEMI,
	PIPE,
	ESCAPE,
} t_lexertype ;	

typedef struct s_lexer 
{
	t_lexertype key;
	char *value;
	struct s_lexer *next;
	struct s_lexer *last;
} t_lexer;





typedef enum e_type
{
	ROUTENODE,
	PIPENODE,
	JOBNODE,
	CMDNODE,
	IONODE,
} e_type

typedef struct s_ROUTENODE
{
	e_type key;
	char *rvalue;
	void *under;
	t_ROUTENODE *next;
} t_ROUTENODE


struct s_PIPENODE
{
	e_type key;
	t_PIPENODE *next_pipe;
	void *left_job;
	void *right_job;
};

struct s_JOBNODE
{
	e_type key;
	t_CMDNODE *cmd;
	t_IONODE *in;
	t_IONODE *out;
}

struct s_CMDNODE
{
	e_type key;
	char **args;
}

struct s_IONODE
{
	e_type key;
	char *value;
	char **files;
	t_IONODE *next_ionode;
}



/*
typedef struct AST AST; // Forward reference

struct AST {
  enum {
    AST_NUMBER,
    AST_ADD,
    AST_MUL,
  } tag;
  union {
    struct AST_NUMBER { int number; } AST_NUMBER;
    struct AST_ADD { AST *left; AST *right; } AST_ADD;
    struct AST_MUL { AST *left; AST *right; } AST_MUL;
  } data;
};*/

