# ifndef INIT_H
# define INIT_H

#include "minishell.h"

/* signals.c */
int init_signals(void);

/* dict.c */
t_dict *init_env_variable();
t_dict *create_dict_on_startup(char **env);
void write_to_dict(t_dict *var, char *key, char *value);
t_dict *search_key_in_dict(t_dict *var, char *arg);
t_dict *get_dict_last(t_dict *dict);

#endif
