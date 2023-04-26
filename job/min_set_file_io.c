/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_set_file_io.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:39:47 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/26 12:08:49 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"






char *ft_set_filename(t_lexer **token, t_dict *dict)
{
    char **values;

    values = min_word_eval(token, dict);

    if (!values)
        return (NULL);
    if (ft_to_many_values(values))
    {
        ft_error_values(values)
        return (NULL);
    }
    return (values[0]);
}



t_lexer *min_set_file_io(t_ionode **end, t_lexer *token, t_dict *dict)
{
    bool    space;
    char    *value;


    space = true;


    while (token && space && *end)
    {
        if (min_token_is_word(token->key) && space)
        {
            space = false;
            value =  ft_set_filename(&token, dict);
        }
       	else if (
            token = token->next;
    }
    if (!value)
        ft_free_end(end);
    return (token)
}

