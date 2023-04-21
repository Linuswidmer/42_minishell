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
    int (*min_export)(t_dict*, char**);
    int (*min_cd)(t_dict *, char**);
	int (*min_pwd)(char **);
	int (*min_env)(t_dict *dict, char **args);
	int (*min_echo)(char **);
} Commands;

typedef struct s_builtins t_builtins;
typedef int (*builtin_ptr)(t_builtins *, char**);

struct s_builtins {
    const char* name;
    builtin_ptr func;
	t_dict *dict;
	Commands commands;
};

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
int		min_export(t_dict *dict, char **arg);

/* cd.c */
int min_cd(t_dict *dict, char **arg);

/* pwd */
int min_pwd(char **args);

/* env.c */
int min_env(t_dict *dict, char **args);

/* echo.c */
int min_echo (char **arg);

/* exit.c */
int min_exit (char **arg);

#endif
