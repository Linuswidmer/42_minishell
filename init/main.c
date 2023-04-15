/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:19:36 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/15 13:27:42 by lwidmer          ###   ########.fr       */
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

int export_wrapper(void** args)
{
    Commands* commands = (Commands*)args[0];
    t_dict* dict = (t_dict*)args[1];
    char* arg = (char*)args[2];

    return (commands->min_export(dict, arg));
}

t_builtins *create_builtins()
{
    t_builtins *builtins;
    int num_builtins;

    num_builtins = 1;

    builtins = malloc(sizeof(builtins) *num_builtins);
    builtins[0].name = ft_strdup("export");
    builtins[0].func = &export_wrapper;
	//builtins[1].name = ft_strdup("cd");
    //builtins[1].func = &cd_wrapper;
    return (builtins);
}

int init_minishell(t_min **min, char **env)
{
	clear_terminal();
	*min = malloc(sizeof(t_min));
	ft_bzero(*min, sizeof(t_min));
	min_status = init_signals();
	// wie machen wir das hier, fragen wir jedes mal status ab?
	(*min)->dict = create_dict_on_startup(env);

	// create builtins here
	(*min)->builtins = create_builtins();
	(*min)->commands.min_export = &min_export;
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
	void **args_export;

	//commands.min_export = &min_export;
	min_status = init_minishell(&min, env);
	//min_export(min->dict, NULL);
    //void* args_export[] = {&commands, min->dict, NULL};
    //void* args_cd[] = {&commands, "./test"};
	args_export = void_args_creator("cds\0", &(min->commands), min->dict, NULL);
	min->builtins[0].func(args_export);
    

	//builtins[1].func(args_cd);
	// readline_loop();
	return (min_status);
}

