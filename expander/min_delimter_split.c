#include "minishell.h"


char **min_delimiter_split(char *value, char *space, char delimiter)
{
        if (!value)
                return (NULL);
        if (*space || *value == delimiter)
                *space = 1;
        if (value[ft_strlen(value) - 1] == delimiter)
                *space += 2;
        return ( ft_split(value, delimiter));
}

