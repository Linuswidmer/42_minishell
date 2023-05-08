/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_set_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:55:49 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/08 09:54:49 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char *ft_set_filename(t_lexer **token, t_dict *dict)
{
    char **values;
	char *filename;

    values = min_word_eval(token, dict);

	printf("v:%s\n", values[0]);
    if (!values)
        return (NULL);
    if (values[1])
    {
    	printf("* to manny in files\n");
        //min_print_error(values)
        return (NULL);
    }
	filename = ft_strdup(values[0]);
	//min_d_free(&values);
    return (filename);
}


static char *ft_set_file_io(t_lexer **token, t_dict *dict)
{
    while (*token)
    {
        if (min_token_is_word((*token)->key))
            return(ft_set_filename(token, dict));
        else if ((*token)->key == l_space)
            *token = (*token)->next;
    }
	return (NULL);
}





int min_set_io(t_lexer **token, t_dict *dict)
{
	t_lexertype key;
	char * filename;
	char * evalhere;

	key = (*token)->key;
	evalhere = (*token)->value;
	*token = (*token)->next; 
	printf("value is %s\n", (*token)->value);
	filename = ft_set_file_io(token, dict);
	printf("filename %s\n", filename);
	if (!filename)
		return (1);
	return (min_ex_io(key, filename, evalhere));
}
 
 
