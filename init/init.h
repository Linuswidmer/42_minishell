# ifndef INIT_H
# define INIT_H

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

extern int min_status;

typedef struct s_dict {
	char *key;
	char *value;
	struct s_dict *next_entry;
}   t_dict;

typedef struct {
    int (*min_export)(t_dict*, char*);
    //int (*cd)(char*);
} Commands;

typedef int (*builtin_ptr)(void**);

typedef struct {
    const char* name;
    builtin_ptr func;
} t_builtins;

typedef struct s_min {
		// dict
		t_dict *dict;
		// builtins
		t_builtins *builtins;
		// Commands
		Commands commands;
		// lexer
		// t_lexer *token;
		// parser AST
		// t_ast *ast;
} t_min;

/* signals.c */
int init_signals(void);

/* dict.c */
t_dict *init_env_variable();
t_dict *create_dict_on_startup(char **env);
void write_to_dict(t_dict *var, char *key, char *value);
t_dict *search_key_in_dict(t_dict *var, char *arg);
t_dict *get_dict_last(t_dict *dict);

/* export.c */
void    print_dict_export(t_dict *dict);
int		min_export(t_dict *dict, char *arg);

#endif
