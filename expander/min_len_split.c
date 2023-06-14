#include "minishell.h"


int min_len_split(char **values)
{
        int n;

        n = 0;
        while (values[n])
                n++;
        return (n);
}

