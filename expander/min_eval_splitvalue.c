#include "minishell.h"

static int ft_check_for_asterisk(char *value)
{
        while (*value)
        {
                if (*value == '*')
                        return (1);
                value++;
        }
        return (0);
}  

static char	ft_asterisk(t_expander **word, t_expander **extra, t_exphelp help)
{
	if (!help.n && help.n == help.len -1 && !help.space)
		return (3);
	else if (help.n == help.len -1 && !help.space)
		return (4);
	else if (!help.n && (!help.space || help.space == 2))
	{               
		if (extra)
                	ft_add_to_asterisk(word, ft_asterisk_splitvalue(splitvalue[help.n]), NULL);
                else
			min_asterisk(NULL, word, ft_asterisk_splitvalue(splitvalue[help.n]), min_init_exphelp(help.dict, 1 ,1));
	}
	else if (extra)
		min_asterisk(NULL, extra, ft_asterisk_splitvalue(splitvalue[help.n]), min_init_exphelp(help.dict, 0 ,1));
	else
		min_asterisk(NULL, word, ft_asterisk_splitvalue(splitvalue[help.n]),  min_init_exphelp(help.dict, 0 ,1));
	return (0);
}

static void ft_normal_extra(t_expander **word, t_expander **extra, t_exphelp help)
{
	if (!n && help.space)
                                {
                                        min_word(NULL, word, splitvalue[n], help.space);
                                }
                                else if(!n)
                                {
                                        min_print_asterisk(*word);
                                        if ( *word && (min_last_expander(*word))->key == l_word)
                                        {
                                                min_word(NULL, word, splitvalue[n], 0);
                                        }
                                        else
                                        {
                                                min_word(NULL, word, splitvalue[n], 1);
                                        }
                                }
                                else
                                        min_word(NULL, extra, splitvalue[n], 1);

}

static void ft_normal(t_expander **word, t_expander **extra, t_exphelp help)
{
	if (extra)
		ft_normal_extra(word, extra , help)
	else
	{
                                if (help.space == 1 || help.space == 3)
                                                min_word(NULL, word, splitvalue[n], help.space);
                                else if (!n)
                                  min_word(NULL, word, splitvalue[n], 0);
                                else
                                        min_word(NULL, word, splitvalue[n], 1);
                        }

}

char     min_eval_splitvalue( t_expander **word, t_expander **extra, t_exphelp help, char **splitvalue)
{
	char	space;
	
        help.len = min_len_split(splitvalue);
        help.n = -1;
        while (word && splitvalue[++help.n])
        {

                if (ft_check_for_asterisk(splitvalue[n]))
                {
			space = ft_asterisk(word, extra, help);
			if (space)
				return (space);			
                }
                else
                {
			ft_normal(word, extra, help);
                }
                if (!help.n && (help.space == 1 || help.space == 3))
                        help.space--;
        }
        return (help.space);
}

