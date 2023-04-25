/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:37:37 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/25 09:59:47 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

int min_unset(t_dict **dict, char **arg)
{
    t_dict *var;
    t_dict *var_prev;
    t_dict *var_next;

    var_prev = *dict;
    var = search_key_in_dict(*dict, arg[0]);
    var_next = var->next_entry;
    if (var == NULL)
        return (0);
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
    return (0);
}
