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

#include "minishell.h"






char *ft_set_filename(t_lexer **token, t_dict *dict)
{
    char **values;

    values = min_word_eval(token, dict);

    if (!values)
        return (NULL);
    if (ft_to_many_values(values))
    {
        //min_print_error(values)
        return (NULL);
    }
    return (values[0]);
}



t_lexer *min_set_file_io(t_ionode **end, t_lexer *token, t_dict *dict)
{
    char    *value;

    while (token && space && *end)
    {
        if (min_token_is_word(token->key))
        {
            value =  ft_set_filename(&token, dict);
		break;	
        }
       	else if (token->key == l_space)
            token = token->next;
	
    }
    if (!value)
        min_free_ionode(end);
    return (token)
}

