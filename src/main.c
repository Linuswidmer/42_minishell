/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:19:36 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/28 11:44:18 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int min_status = 0;

int readline_loop(t_min *min)
{
	char *readline_input;
	int exit;	

	min_status = 0; 
	
	exit = 0;
	//printf("min_status %i\n", min_status);
	while (exit == 0)
	{
		readline_input = readline("minishell> ");
    	if (readline_input == NULL)
   		{
			free(readline_input);
			break ;
		}
		min->token = lexer(&readline_input);
		min->ast = min_parser(min->token);
		printf("hallo\n");
		exit = min_executer(min->ast, min->dict, min->builtins);
		// expander /  executer
		add_history(readline_input);
		free(readline_input);
		free_token_list(&(min->token));
	}
	free_dict(min->dict);
	free_builtins(min->builtins);
	free_min(min);
	return (min_status);
}

int main(int argc, char **argv, char **env) 
{
	t_min *min;

	(void)argc;
	(void)argv;

	init_signals();
	min_status = init_minishell(&min, env);

	readline_loop(min);
	//test_builtins(min);

	return 0;
}

