#include "minishell.h"


char    min_add_value_to_expander(t_lexer **token, t_expander **word, char **result, char space)
{
        if (!*result)
                min_free_expander(word);
        else
        {   
                min_word(token, word, *result, space);
                min_free(result);
        }   
        return (0);
}

