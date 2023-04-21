/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:19:36 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/21 17:43:40 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "libft.h"

int min_status = 0;

void clear_terminal(void) 
{
  printf("\033[2J");
  printf("\033[H");
}

int export_wrapper(t_builtins *builtin, char **args)
{
    return (builtin->commands.min_export(builtin->dict, args));
}

int cd_wrapper(t_builtins *builtin, char **args)
{
	return (builtin->commands.min_cd(builtin->dict, args));
}

int pwd_wrapper(t_builtins *builtin, char **args)
{
	return (builtin->commands.min_pwd(args));
}

int env_wrapper(t_builtins *builtin, char **args)
{
	return (builtin->commands.min_env(builtin->dict, args));
}

/*
int env_wrapper(void **args)
{
	Commands *commands;
	t_dict *dict;
	char **arg;

	commands = (Commands*)args[0];
	dict = (t_dict*)args[1];
	arg = (char **)&(args[2]);
	return(commands->min_env(dict, arg));
}
*/


t_builtins *create_builtins(t_dict *dict, Commands *commands)
{
    t_builtins *builtins;
    int num_builtins;

    num_builtins = 40;

    builtins = malloc(sizeof(builtins) *num_builtins);
    builtins[0].name = ft_strdup("export");
    builtins[0].func = &export_wrapper;
	builtins[0].dict = dict;
	builtins[0].commands = *commands;
	builtins[1].name = ft_strdup("cd");
    builtins[1].func = &cd_wrapper;
	builtins[1].dict = dict;
	builtins[1].commands = *commands;
	builtins[2].name = ft_strdup("pwd");
    builtins[2].func = &pwd_wrapper;
	builtins[2].dict = dict;
	builtins[2].commands = *commands;
	builtins[3].name = ft_strdup("env");
    builtins[3].func = &env_wrapper;
	builtins[3].dict = dict;
	builtins[3].commands = *commands;

	/*
	builtins[2].name = ft_strdup("pwd");
    builtins[2].func = &pwd_wrapper;
	builtins[3].name = ft_strdup("env");
    builtins[3].func = &env_wrapper;
    */
	return (builtins);
}

int init_minishell(t_min **min, char **env)
{
	//clear_terminal();
	*min = malloc(sizeof(t_min));
	ft_bzero(*min, sizeof(t_min));
	min_status = init_signals();
	// wie machen wir das hier, fragen wir jedes mal status ab?
	(*min)->dict = create_dict_on_startup(env);

	// create builtins here
	(*min)->commands.min_export = &min_export;
	(*min)->commands.min_cd = &min_cd;
	(*min)->commands.min_pwd = &min_pwd;
	(*min)->commands.min_env = &min_env;
	(*min)->commands.min_echo = &min_echo;
	(*min)->commands.min_exit = &min_exit;
	(*min)->commands.min_unset = &min_unset;
	(*min)->commands.min_env = &min_env;
	(*min)->builtins = create_builtins((*min)->dict, &(*min)->commands);
	return (0);
}

int readline_loop()
{
  char *readline_input;

  min_status = 0; // global variable does not work yet
  // printf("min_status %i\n", min_status);
  while (min_status == 0)
  {
	  readline_input = readline("minishell> ");
    if (readline_input == NULL)
    {
      free(readline_input);
      break ;
    }
    // lexer
    // parser
    // expander
    // executer
    add_history(readline_input);
    free(readline_input);
  }
  return (0);
}

/*
c = commands
d = dict
s = string
*/
void **void_args_creator(const char *arg_types, ...)
{
	int i;
	int num_args;
	void **args;
	va_list ap;

	va_start(ap, arg_types);
	i = 0;
	num_args = ft_strlen(arg_types);
	args = malloc(sizeof(void *) * num_args);
	while (arg_types[i] != '\0')
	{
		if (arg_types[i] == 'c')
			args[i] = va_arg(ap, Commands *);
		if (arg_types[i] == 'd')
			args[i] = va_arg(ap, t_dict *);
		if (arg_types[i] == 's')
			args[i] = va_arg(ap, char *);
		i++;
	}
	va_end(ap);
	return (args);
}

int main(int argc, char **argv, char **env) 
{
	t_dict *dict;
	char *readline_input;
	t_min *min;
	Commands  commands;
	char **args_export;
	//void **args_export;
	char **args_cd;
	char **args_pwd;
	char **args_env;

	min_status = init_minishell(&min, env);

	/*	
	args_export = malloc(sizeof(char *) *1);
	args_export[0] = NULL;
	min->builtins[0].func(&(min->builtins[0]), args_export);
	*/

	/*
	args_cd = malloc(sizeof(char *) *2);
	args_cd[0] = ft_strdup("-");
	args_cd[1] = NULL;	
	min->builtins[1].func(&(min->builtins[1]), args_cd);
	*/

	/*
	args_pwd = malloc(sizeof(char *) * 1);
	args_pwd[0] = NULL;
	min->builtins[2].func(&(min->builtins[2]), args_pwd);
	*/

	args_env = malloc(sizeof(char *) * 1);
	args_env[0] = NULL;
	min->builtins[3].func(&(min->builtins[3]), args_env);

// readline_loop();
	return (min_status);
}

