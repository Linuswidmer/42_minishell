#include "minishell.h"



static void     ft_free_lexernode(t_lexer **token_list)
{
        if (*token_list)
                {
                        if ((*token_list)->value)
                                free((*token_list)->value);
                        free(*token_list);
                        *token_list = NULL;
                }
}

static void 	ft_space(t_lexer **file)
{

        while (*file && (*file)->key == l_space)
        {
                if ((*file)->next)
		{
                        *file = (*file)->next;
                        ft_free_lexernode(&(*file)->prev);
		}
        }

}

static void	ft_word(t_lexer **file, t_lexer *token)
{
	print_token_list(*file);
	print_token_list((*file)->prev);
	print_token_list(token->prev);	
        while (*file && min_token_is_word((*file)->key))
        {
		
		ft_printf_fd("l\n", 2);
                if ((*file)->next)
                {
                        *file = (*file)->next;
                if ( (*file)->prev != token )
                        ft_free_lexernode(&(*file)->prev);
                
		}
		else
		{
			//ft_free_lexernode(file);
			if ((*file)->prev != token->prev )	
			{
				ft_printf_fd("done\n", 2);
                        	ft_free_lexernode(file);
			}
			else
				*file = NULL;		
			break;
		}
        }		
}





/* set path to next next wrd and delete the others*/
t_lexer  *min_here_set_file(t_lexer *token, char *path)
{
        t_lexer *file;
        char    *old;

        file = token;
        old = token->value;
        token->key = l_word;
        token->value = path;
        min_free(&old);
        if (file->next &&  !min_token_is_word(file->key))
                       file = file->next;
	ft_space(&file);
	ft_word(&file, token);
	print_token_list(file);
        token->next = file;
        if (file)
                file->prev = token;
        return (token);
}

