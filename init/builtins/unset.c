/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:37:37 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/09 14:43:43 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int min_unset(t_dict **dict, char **arg)
{
    t_dict *var;
    t_dict *var_prev;
    t_dict *var_next;

    var_prev = *dict;
    var = search_key_in_dict(*dict, arg[0]);
	if (var)
    	var_next = var->next_entry;
    if (var == NULL)
        return (1000);
    else if (var == *dict)
    {
        *dict = var_next;
        var_prev = NULL;
    }
    else
    {
        while (var_prev->next_entry != var)
            var_prev = var_prev->next_entry;
    }
    free(var->value);
    free(var->key);
    free(var);
    if (var_prev)
        var_prev->next_entry = var_next;
    return (1000);
}
