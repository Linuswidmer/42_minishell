/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:19:36 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/23 13:31:46 by jstrotbe         ###   ########.fr       */
/*   Updated: 2023/06/22 10:11:21 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/05/11 14:48:19 by jstrotbe         ###   ########.fr       */
/*   Updated: 2023/05/11 10:06:48 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/05/11 09:53:34 by jstrotbe         ###   ########.fr       */
/*   Updated: 2023/05/03 09:45:15 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/05/02 18:00:09 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_status = 1;

void	free_minishell(t_min *min)
{
	close(min->in);
	close(min->out);
	free_dict(min->dict);
	free_builtins(min->builtins);
	free_min(min);
}

int	lex_parse_exec(t_min *min, char **readline_input)
{
	int	exit;

	exit = 0;
	min->token = lexer(readline_input);
	if (min->token)
	{
		min->ast = min_parser(min->token);
		if (min->ast) 
			exit = min_executer(min->ast, min->dict, min->builtins, 1);
		else
			g_status = 2;
	}	
	else
		g_status = 2;
	return (exit);
}

int set_g_status(int exit)
{
	if (exit >= 1000 && exit < 2000)
	{
		g_status = exit - 1000;
		return (0);
	}
	return (exit);
}

void	free_resources_readline_loop(char *readline_input, t_min *min)
{
	free(readline_input);
	min_free_ast(&min->ast);
	free_token_list(&(min->token));
}

int ft_readline_loop(t_min *min)
{
	char *readline_input;
	static int exit;	

	while (!exit && min->dict)
	{
		exit = init_signals();
		readline_input = readline("minishell> ");
    	if (!readline_input)
   		{
			free(readline_input);
			exit = 1;
			break;	
		}
		if (_DEBUG)
			ft_printf_fd("\n \\DEBUG_MODE\\ \n\n", 2);
		exit = lex_parse_exec(min, &readline_input);
		add_history(readline_input);
		free_resources_readline_loop(readline_input, min);
		dup2(min->in, STDIN_FILENO);
		dup2(min->out, STDOUT_FILENO);
		exit = set_g_status(exit);
	}
	free_minishell(min);
	return (exit);
}

int main(int argc, char **argv, char **env) 
{
	t_min *min;
	int	exit;
	
	(void)argc;
	(void)argv;
	
	exit = init_minishell(&min, env);
	if (!exit)
		exit = ft_readline_loop(min);
	if (exit == 256)
		exit = 0;
	return (exit);
	return(0);
}

