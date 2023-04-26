/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:19:36 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/26 10:23:43 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int min_status = 0;

int test_builtins(t_min *min)
{
	int status;
	char **args_export;
	char **args_cd;
	char **args_pwd;
	char **args_env;
	char **args_echo;
	char **args_exit;
	char **args_unset;

	args_export = malloc(sizeof(char *) *1);
    args_export[0] = NULL;
    min->builtins[0].func(&(min->builtins[0]), args_export);
	free(args_export);

	/*
	status = 0;
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

    /* 
    args_env = malloc(sizeof(char *) * 1);
    args_env[0] = NULL;
    min->builtins[3].func(&(min->builtins[3]), args_env);
    */

    /*
    args_echo = malloc(sizeof(char *) * 3);
    args_echo[0] = ft_strdup("-n");
    args_echo[1] = ft_strdup("world");
    args_echo[2] = NULL;
    min->builtins[5].func(&(min->builtins[5]), args_echo);
    */

    /*
    args_exit = malloc(sizeof(char *) * 2);
    args_exit[0] = ft_strdup("22");
    args_exit[1] = NULL;
    status = min->builtins[4].func(&(min->builtins[4]), args_exit);
    printf("status: %i", status);   
    */
	args_unset = malloc(sizeof(char *) * 2);
    args_unset[0] = ft_strdup("HOME");
    args_unset[1] = NULL;
    //min->builtins[6].func(&(min->builtins[6]), args_unset);

    min->builtins[0].func(&(min->builtins[0]), args_export);

	return (status);
}


int readline_loop(t_min *min)
{
	char *readline_input;

	min_status = 0; 
	//printf("min_status %i\n", min_status);
	while (min_status == 0)
	{
		readline_input = readline("minishell> ");
    	if (readline_input == NULL)
   		{
			free(readline_input);
			break ;
		}
		min->token = lexer(readline_input);
		min->ast = min_parser(min->token);
		// expander /  executer
		add_history(readline_input);
		free(readline_input);
		//free_token_list(&(min->token));
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

