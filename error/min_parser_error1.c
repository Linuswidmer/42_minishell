/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_parser_error1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:32:15 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/08 15:00:01 by jstrotbe         ###   ########.fr       */
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
	else
		return (NULL);
}




void	min_parser_error1(t_ast **ast, t_lexertype key, char *value)
{
	if (value)
	{
		printf("syntax error near unexpected token: %s\n", value);
	}		
  	else
	{		 printf("syntax error near unexpected token: %s\n", ft_get_token(key));

	}
	//min_free_ast(ast);
	if (ast)
		*ast = NULL;
}
