/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:19:36 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/28 09:50:31 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_readline_loop(t_min *min)
{
	char *readline_input;
	int exit;	
	
	exit = 0;
	//printf("min_status %i\n", min_status);
	while (!exit)
	{
		readline_input = readline("minishell> ");
    	if (!readline_input)
   		{
			free(readline_input);
			exit = 1;
			break;	
		}
		min->token = lexer(&readline_input);
		if (min->token)
		{
			min->ast = min_parser(min->token);
			if (min->ast) 
				exit = min_executer(min->ast, min->dict, min->builtins);
			else
				exit = 1;
		}
		else
				exit = 1;
		add_history(readline_input);
		free(readline_input);
		//min_free_ast(&min->ast)
		free_token_list(&(min->token));
	}
	free_dict(min->dict);
	free_builtins(min->builtins);
	free_min(min);
	return (exit);
}

int main(int argc, char **argv, char **env) 
{
	t_min *min;
	int	exit;
	
	(void)argc;
	(void)argv;
	exit = init_signals();
	exit = init_minishell(&min, env);

	if (!exit)
		exit = readline_loop(min);
	return (exit);
}

