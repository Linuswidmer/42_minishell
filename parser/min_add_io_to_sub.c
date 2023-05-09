/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_add_io_to_sub.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:04:41 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/09 12:30:52 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_lexer *min_add_io_to_sub(t_lexer *token, t_ast **ast)
{
	char io;
		
	if (min_token_is_word(token->key))	
		min_parser_error(ast, token->key, token->value);
	else
	{
		(*ast)->node.sub->start = token;
		while (token)
		{
			while (token && token->key == l_space)
					token = token->next;
			if (token && ((min_token_is_io(token->key) || min_token_is_word(token->key))))
			{
				if (min_token_is_io(token->key) == 2 && !io)
                {   
              		if (min_heredoc(&token, HEREDOC))
                    {
                    	min_heredoc_fail(ast);
                        printf("heredoc error io file\n");
                        break;
                     }
                }
				else if (min_token_is_word(token->key) && !io)
                {
                	printf("error sub cmd\n");
                    *ast = NULL;
                    break;
                }
                else if (min_token_is_io(token->key))
                {
                	if( !io)
                    	io = 1;
                    else
                    {
                       	printf("error io1 file\n");
                            *ast = NULL;
                            break;
                    }
					if (token->next)
						token = token->next;
					else
					{
						min_parser_error(ast, token->key, P_NEWLINE);	
						break;
					}
				}
				while (token && token->key == l_space)
                        token = token->next;
				while (token && token->next && min_token_is_word(token->key))
				{
						token = token->next;
						io = 0;
				}
	    		if (!token->next && io && !min_token_is_word(token->key))
				{	
					printf("error io2 file\n");
                            *ast = NULL;
                            break;
				}
				else
					token = token->next;
			}
			else if (io)
			{
				 printf("error io3 file\n");
                            *ast = NULL;
                            break;
			}
			else
				break;
		}		
		
	if (*ast)
	{
			(*ast)->node.sub->last = token;
                printf("[ %p ]\n", (*ast)->node.sub->last = token);   	
	}	
 	}
	return (token);		
}
