/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:19:36 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/11 10:06:48 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/05/11 09:53:34 by jstrotbe         ###   ########.fr       */
/*   Updated: 2023/05/03 09:45:15 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/05/02 18:00:09 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_status = 1;

int ft_readline_loop(t_min *min)
{
	char *readline_input;
	int exit;	
	
	exit = 0;
	//printf("min_status %i\n", min_status);
	while (!exit && min->dict)
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
				exit = min_executer(min->ast, min->dict, min->builtins, 1);
			else
				exit = 2;
		}	
		else
				exit = 2;
		
		add_history(readline_input);
		free(readline_input);
		//min_free_ast(&min->ast);
		free_token_list(&(min->token));
		dup2(min->in, STDIN_FILENO);
		dup2(min->out, STDOUT_FILENO);
		/*if (exit >= 3000)	
		{
			g_status = exit - 3000;
			printf("gstatus is %i\n", g_status);
			exit = 0;
		}
		else */ if (exit >= 1000 && exit < 2000)
		{
			g_status = exit - 1000;
			printf("\nstatus is %i\n", g_status);
                        exit = 0;
		}	
	}
	close(min->in);
	close(min->out);
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
		exit = ft_readline_loop(min);
	if (exit == 256)
		exit = 0;
	printf("\nexit: %i \n", exit); 
	return (exit);
}

