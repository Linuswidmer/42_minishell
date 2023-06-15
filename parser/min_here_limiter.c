#include "minishell.h"


static char	*ft_limiter_loop(t_lexer *token, char *limiter)
{

        char    *temp;
                while (limiter && token && min_token_is_word(token->key))
                {   
                        temp = limiter;
                        if (min_token_is_word(token->key) == 2)
                                limiter = ft_strjoin(limiter, DOLLAR);
                        else if (min_token_is_word(token->key) == 3)
                                limiter = ft_strjoin(limiter, ASTERISK);
                        else
                                limiter = ft_strjoin(limiter, token->value);
                        token = token->next;
			min_free(&temp);
                }   
                return (limiter);
}




char     *min_here_limiter(t_lexer *token)
{
        char    *limiter;

        limiter = ft_strdup(EMPTY);
        while (token && token->key == l_space)
                token = token->next;
        if (!token)
                min_parser_error(NULL, 0, P_NEWLINE);
        else
                limiter = ft_strdup(EMPTY);
        if (limiter && token && min_token_is_word(token->key))
        {
		return (ft_limiter_loop(token, limiter));
        }   
        else
                return (NULL);
}

