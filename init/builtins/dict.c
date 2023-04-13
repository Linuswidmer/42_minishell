/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:25:40 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/12 16:28:59 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

void    print_dict(t_dict *dict)
{
    while (dict)
    {   
        printf("%s=%s\n", dict->key, dict->value);
        dict = dict->next_entry;
    }   
}

void create_dict_on_startup(t_dict *var1, char **env)
{
    t_dict *var2;
    char **split_str;
    int i;

    i = 1;
    split_str = ft_split(env[0], '=');
    write_to_env_variable(var1, split_str[0], split_str[1]);
    while (env[i])
    {
        var2 = init_env_variable();
        var1->next_entry = var2;
        var1 = var2; 
        split_str = ft_split(env[i], '=');
        write_to_env_variable(var1, split_str[0], split_str[1]);
        free(split_str[2]);
        i++;
    }
}
