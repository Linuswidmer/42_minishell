/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:19:36 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/07 17:50:59 by jstrotbe         ###   ########.fr       */
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

int init_minishell(t_min **min, char **env)
{
  clear_terminal();
  *min = malloc(sizeof(t_min));
  ft_bzero(*min, sizeof(t_min));
  min_status = init_signals();
  // wie machen wir das hier, fragen wir jedes mal status ab?
  (*min)->dict = create_dict_on_startup(env);

  // create builtins here
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

int main(int argc, char **argv, char **env) 
{
	t_dict *dict;
	char *readline_input;
  t_min *min;

  min_status = init_minishell(&min, env);
	// print_dict_export(min->dict);
  min_export(min->dict, NULL);
  // readline_loop();
	return (min_status);
}

