#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

/* AST struct */
typedef struct s_PIPENODE t_PIPENODE;
typedef struct s_JOBNODE t_JOBNODE;
typedef struct s_CMDNODE t_CMDNODE;
typedef struct s_IONODE t_IONODE;
typeded struct s_ROUTENODE t_ROUTENODE;

typedef enum e_type
{
	ROUTENODE,
	PIPENODE,
	JOBNODE,
	CMDNODE,
	IONODE,
} e_type

struct s_ROUTENODE
{
	e_type key;
	char *rvalue;
	void *up;
	void *down;
	t_ROUTENODE *next;
	t_ROUTENODE *last;
}


struct s_PIPENODE
{
	e_type key;
	t_PIPENODE *next;
	t_PIPENODE *last;
	void *up;
	void *left_job;
	void *right_job;
};

struct s_JOBNODE
{
	e_type key;
	void *up;
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

/* FUNCTIONS */

void    *min_parser(t_lexer *token);

/* ROUTE */
t_lexer *min_ROUTENODE(t_lexer *token, void **ast);
int	min_is_PARA(t_lexertype key);
int     min_is_ROUTE(t_lexertype key);



/* PIPE */
t_lexer *min_PIPENODE(t_lexer *token, void **ast);

/* JOBNODE */
t_lexer	*min_JOBENODE(t_lexer *token, void **ast);

/* IO */
int     min_is_IO(t_lexertype key);

/* WORD */
int     min_is_WORD(t_lexertype kWORD
	
#endif
