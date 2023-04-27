#ifndef EXECUTER_H
# define EXECUTER_H

int     min_job(t_ast *ast, t_dict *dict, t_builtins *build  );
int	min_executer(t_ast *ast, t_dict *dict, t_builtins *build);
int 	min_exit_handler(int exit);

#endif
