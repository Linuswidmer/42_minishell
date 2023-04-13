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

typedef struct s_min
{
		// dict
		t_dict *dict;
		// lexer
		// t_lexer *token;
		// parser AST
		// t_ast *ast;
} t_min;

/* signals.c */
int init_signals(void);

/* dict.c */
t_dict *init_env_variable();
void create_dict_on_startup(t_dict *var1, char **env);
void    print_dict(t_dict *dict);
void write_to_env_variable(t_dict *var, char *key, char *value);

#endif
