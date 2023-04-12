/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:25:45 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/12 17:06:35 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

/*
min_builtins *create_builtins()
{
	min_builtins *builtins;
	int num_builtins;

	num_builtins = 2;

	builtins = malloc(sizeof(builtins) *num_builtins);
	builtins[0].name = ft_strdup("export");
	builtins[0].func = &export_wrapper;
	builtins[1].name = ft_strdup("cd");
	builtins[1].func = &cd_wrapper;
	return (builtins);
}
*/

int main(int argc, char **argv, char **envp)
{
	t_dict *dict;
	Commands	commands;
	min_builtins *builtins;

	commands.export = &export;
	commands.cd = &cd; 

    dict = init_env_variable();
    create_dict_on_startup(dict, envp);
    
	cd("../../", dict);
	//export(dict, "newvar22_323=100");
    //export(dict, "newvar22_3=");
    //export(dict, "new");
	//printf("enters here\n");
    //export(dict, NULL);
	//env(dict);
	//unset(&dict, "SYSTEMD_EXEC_PID");
    //export(dict, NULL);
	

	//builtins = create_builtins();
	//void* args_export[] = {&commands, dict, NULL};
	//void* args_cd[] = {&commands, "./test"};
	//builtins[0].func(args_export);
    //builtins[1].func(args_cd);

	//cd("..");
	//export(dict, "_");
    //export(dict, "_l");
    //export(dict, "12345");
    //export(dict, "new_var");
    //export(dict, "new_var=100");
    //export(dict, NULL);
}
