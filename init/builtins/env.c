/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:29:59 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/21 16:33:08 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

void    print_dict_env(t_dict *dict)
{
    while (dict)
    {
        printf("%s=%s\n", dict->key, dict->value);
        dict = dict->next_entry;
    }
}

int min_env(t_dict *dict, char **args)
{
	printf("%s", args[0]);
	if (args[0])
		printf("env: too many arguments\n");
	else 
		print_dict_env(dict);
	return (0);
}
