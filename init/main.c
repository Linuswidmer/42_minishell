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

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "init.h"

void clear_terminal(void) 
{
  printf("\033[2J");
  printf("\033[H");
}

void handle_sigint(int sig) 
{
  char c;

  c = 10;
	// printf("\n");
  write(0, &c, 1);
}

void handle_sigquit(int sig) {
    printf("Received SIGQUIT signal\n");
	// exit(1);
}

int init_signals()
{
	struct sigaction sa_sigint;
	struct sigaction sa_sigquit;

	sa_sigint.sa_handler = handle_sigint;
	sigemptyset(&sa_sigint.sa_mask);
	sa_sigint.sa_flags = 0;

	sa_sigquit.sa_handler = handle_sigquit;
  sigemptyset(&sa_sigquit.sa_mask);
  sa_sigquit.sa_flags = 0;

	if (sigaction(SIGINT, &sa_sigint, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}
	if (sigaction(SIGQUIT, &sa_sigquit, NULL) == -1) {
    perror("sigaction");
    return (1);
  }

  return (0);
}

int init(void)
{
  int status;

  clear_terminal();
  status = init_signals();
}

int readline_loop()
{
  char *readline_input;

	readline_input = readline("minishell> ");
  if (readline_input != NULL)
  {
    add_history(readline_input);
    free(readline_input);
    readline_loop();
  }

  return (0);
}

int main() 
{
  int status;
	char *readline_input;

  status = init();
	readline_loop();
  // while (1)
	// {
	// 	readline_input = readline("minishell> ");
	// 	if (readline_input == NULL)
	// 	{
	// 		free(readline_input);
	// 		break;
	// 	}
 //    printf("%s\n", readline_input);
	// 	add_history(readline_input);
	// 	free(readline_input);
	// }
	return 0;
}

