/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:19:36 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/07 13:08:12 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

void clear_terminal() 
{
  // Save cursor position
  printf("\033[s");

  // Clear screen
  printf("\033[2J");

  // Move cursor to top left corner
  printf("\033[H");
}

int main() 
{
	clear_terminal();
 	t_lexer *first;
	char *readline_input;
	t_lexer *token_list;

	while (1)
	{
		readline_input = readline("minishell> ");
		if (readline_input == NULL)
		{
			free(readline_input);
			break;
		}
		add_history(readline_input);
		token_list = lexer(readline_input);
		print_token_list(token_list);
		free(readline_input);
	}
	return 0;
}

