# ifndef INIT_H
# define INIT_H

/* signals.c */
int init_signals(void);
void sigint_in_job(int sig);

/* dict.c */
t_dict *init_env_variable();
t_dict *create_dict_on_startup(char **env);
void write_to_dict(t_dict *var, char *key, char *value);
t_dict *search_key_in_dict(t_dict *var, char *arg);
t_dict *get_dict_last(t_dict *dict);

/*init.c*/
int init_minishell(t_min **min, char **env);

/* free_dict_builtins_min */
int free_dict(t_dict *dict);
int free_builtins(t_builtins *builtins);
int free_min(t_min *min);

#endif
