/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:25:45 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/12 13:07:21 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"


int unset(t_dict *dict, char *arg)
{
	t_dict *var;
	t_dict *var_prev;
	t_dict *var_next;

	var_prev = dict;
	var = search_key_in_dict(dict, arg);
	if (var != NULL)
		printf("key found\n");
	else
		return (0);
	while (var_prev->next_entry != var)
		var_prev = var_prev->next_entry;
	var_next = var->next_entry;

	free(var->value);
	free(var->key);
	free(var);
	var_prev->next_entry = var_next;
	return (0);
}

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

int main(int argc, char **argv, char **env)
{
	t_dict *dict;
	Commands	commands;
	min_builtins *builtins;

	commands.export = &export;
	commands.cd = &cd; 

    dict = init_env_variable();
    create_dict_on_startup(dict, env);
    export(dict, "new_var=100");
    export(dict, NULL);
	unset(dict, "SHELL");
    export(dict, NULL);
	

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

