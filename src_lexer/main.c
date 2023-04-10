/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:03:49 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/10 10:12:05 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int main(int argc, char **argv)
{
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
	token_list = lexer(readline_input);
    print_token_list(token_list);
    free(readline_input);
	free_token_list(token_list);
  }
}
