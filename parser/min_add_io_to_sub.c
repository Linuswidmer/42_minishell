/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_add_io_to_sub.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:04:41 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/10 19:27:12 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_token_is_jobnode(t_lexertype key)
{
    if (min_token_is_io(key) || min_token_is_word(key)
            || key == l_space)
        return (1);
    else
        return (0);
}


static int  ft_token_not_valid(t_lexer **token, t_ast ** ast, char *io)
{
        if (min_token_is_io((*token)->key) == 2 && !*io)
        {
            if (min_heredoc(token, HEREDOC))
                return (min_heredoc_fail(ast));
        }
        else if (min_token_is_io((*token)->key))
                {
                if(!*io)
                    *io = 1;
                else
                    return(min_parser_error(ast, (*token)->key, NULL));
        }
        else if (min_token_is_word((*token)->key) && *io)
               *io = 0;
		else if (min_token_is_word((*token)->key) && !*io)
			return(min_parser_error(ast, (*token)->key, (*token)->value));
        if ((*token)->next || !*io)
            return (0);
        else
            return (min_parser_error(ast, (*token)->key, P_NEWLINE));
}


static t_lexer  *ft_find_last_token(t_lexer *token, t_ast **ast)
{
    char io;

    io = 0;
    while (token)
    {
        if (ft_token_is_jobnode(token->key))
        {
            if (ft_token_not_valid(&token, ast, &io))
                break;
            token = token->next;
        }   
        else
        {
            if (io)
			{	
				printf("test2\n");
                min_parser_error(ast, token->key, NULL);
			}
            break;
        }
    }
    return (token);
}



t_lexer *min_add_io_to_sub(t_lexer *token, t_ast **ast)
{
	char io;
		
	if (min_token_is_word(token->key))	
		min_parser_error(ast, token->key, token->value);
	else
	{
		(*ast)->node.sub->start = token;
		token = ft_find_last_token(token, ast);
		if (*ast)
			(*ast)->node.sub->last = token;
	}
	return (token);
}	
/*		
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
					min_parser_error(ast, token->key, NULL);
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
}*/
