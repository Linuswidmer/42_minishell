#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_dict t_dict;
typedef struct s_min t_min;
typedef struct s_builtins t_builtins;
typedef int (*builtin_ptr)(t_builtins *, char**);
typedef struct s_commands t_commands;
typedef struct s_lexer t_lexer;

typedef enum 
{
	l_empty,
	l_dquote,
	l_quote,
	l_word,
	l_asterisk,
	l_paraopen,
	l_paraclose,
	l_heredoc,
	l_append,
	l_in,
	l_out,
	l_dollar,
	l_and,
	l_or,
	l_semi,
	l_pipe,
	l_escape,
	l_space,
	l_amp,
} t_lexertype ;	


/* buildins*/
struct s_commands{
    int (*min_export)(t_dict*, char**);
    int (*min_cd)(t_dict *, char**);
	int (*min_pwd)(char **);
	int (*min_env)(t_dict *dict, char **args);
	int (*min_echo)(char **);
	int (*min_exit)(char **);
	int (*min_unset)(t_dict **, char **);
};

struct s_builtins {
    const char* name;
    builtin_ptr func;
	t_dict *dict;
	t_commands commands;
};


/*   dict */
struct s_dict {
	char *key;
	char *value;
	t_dict *next_entry;
}

/*lexer*/
struct s_lexer {
	t_lexertype key;
	char *value;
	t_lexer *next;
	t_lexer *prev;
};

/* main */
struct {
		// dict
		t_dict *dict;
		// builtins
		t_builtins *builtins;
		// Commands
		t_commands commands;
		// lexer
		t_lexer *token;
		// parser AST
		t_ast *ast;
} t_min;

#endif
