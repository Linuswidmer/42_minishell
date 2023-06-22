/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_parser_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:32:15 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/21 15:06:44 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"






char *ft_get_token(t_lexertype key)
{
	if (key == l_append)
		return (APPEND);
	else if (key == l_in)
		return (IN);
	else if (key == l_out)
 		return (OUT);
	else if (key == l_asterisk)
		return (ASTERISK);
	else if (key == l_paraopen)
		return (PARAOPEN);
	else if (key == l_paraclose)
		return (PARACLOSE);
	else if (key == l_heredoc)
    	return (L_HEREDOC);
	else if (key == l_dollar)
		return (DOLLAR);
	else if (key == l_and)
		return(L_AND);
	else if (key == l_or)
		return (L_OR);
	else if (key == l_semi)
    	return (L_SEMI);	
	else if (key == l_pipe)
		return (L_PIPE);
	else if (key == l_til)
		return (L_TIL);
	else if (key == l_space)
		return ("kkk");
	else
		return (NULL);
}




int	min_parser_error(t_ast **ast, t_lexertype key, char *value)
{
	if (value)
	{
		ft_printf_fd("syntax error near unexpected token: '%s'\n",2, value );
	}		
  	else
	{		 ft_printf_fd("syntax error near unexpected token: '%s'\n",2, ft_get_token(key));

	}
	min_free_ast(ast);
	if (ast)
		*ast = NULL;
	return (1);
}
