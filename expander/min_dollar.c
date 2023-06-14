/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_dollar_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:00:18 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/12 16:22:26 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **ft_delimiter_split(char *value, char *space, char delimiter)
{
	if (!value)
		return (NULL); 
	if (*space || *value == delimiter)
		*space = 1;
	if (value[ft_strlen(value) - 1] == delimiter)
		*space += 2;
	return ( ft_split(value, delimiter));
}

static int	ft_add_last_expander(t_expander **word, char *value, t_lexertype key)
{
	t_expander  *end;

        if (!*word)
        {
                *word = min_init_expander(key, value);
                if (!*word)
                        return (1);
        }
        else
	{
                end = min_last_expander(*word);
        	end->next =  min_init_expander(key, value);
                if (!(*word)->next)
                {
                        min_free_expander(word);
                	return (1);
               }
         }
        
        return (0);
}

	

static void	ft_get_dollar_asterisk(char **values, char space, t_expander **old)
{
	int n;
	
	if (!values)
	{	
		*old = NULL;
		return ;
	}	
        n = 0;
	if (space == 1 || space == 3)
		ft_add_last_expander(old,EMPTY , l_asterisk);
	if ((space == 1 || space == 3) && (!old || !values[n]))
		return ;
	ft_add_last_expander(old, values[n], l_word);
        while (old && values[++n])
	{
		ft_add_last_expander(old, EMPTY, l_asterisk);
		if (old)
			ft_add_last_expander(old, values[n], l_word);		
	}
	if (old && (space == 2 || space == 3))
		 ft_add_last_expander(old, EMPTY, l_asterisk);
}
    	
/* make from str asterisk and check for last entry in asterisk row*/
static t_expander *ft_asterisk_splitvalue(char *value)
{
	char	**values;
	char	space;
	t_expander *old;

	old = NULL;
	space = 0;
	values = ft_delimiter_split(value, &space, E_ASTERISK);
	ft_get_dollar_asterisk(values, space, &old);
	//min_doublefree(&values);
	if (!old)
                ft_putstr_fd(ERR_MALL, 2);
	return (old);
}

static int ft_len_split(char **values)
{
	int n;

	n = 0;
	while (values[n])
		n++;
	return (n);
}
		

static char	ft_add_to_asterisk(t_expander **word, t_expander *new, t_lexer **token)
{
	char *oldword;
		
	if ((new && new->key == l_word) && (*word && (min_last_expander(*word))->key == l_word))
        {
                oldword = (min_last_expander(*word))->word;
                (min_last_expander(*word))->word = ft_strjoin(oldword, new->word);
                min_free(&oldword);
		(min_last_expander(*word))->next = new->next; 
        }
        else if (*word)
		(min_last_expander(*word))->next = new;
	min_free_expander(&new);
	if (*token)
		(*token) = (*token)->next;
	return (0);
}


static char	ft_special_next_token(t_lexer **token, t_expander **word, t_expander **extra, t_exphelp help)
{
	if (!(*token) || (*token && !min_token_is_word((*token)->key)))
        {   
                if (extra)
                        return (min_to_aste(word, min_init_expander(l_word, DOLLAR), token));
                min_word(NULL, word, DOLLAR, help.space);
                return (1);
        }    
        else if ((*token)->key == l_dollar)
        {   
                ft_putstr_fd(ERR_ID, 2); 
                 if (extra)
                           return (min_to_aste(word, min_init_expander(l_word, DDOLLAR), token));
                return (min_word(token, word, DDOLLAR, help.space));
        }    
        else if ((*token)->key == l_til)
        {   
                 if (extra)
                    return (min_to_aste(word, min_init_expander(l_word, DTIL), token));
                return (min_word(token, word, DTIL, help.space));
        }
	return (help.space);   	
}

static int	ft_next_is_special(t_lexer **token)
{
	 if (!(*token) || (*token && !min_token_is_word((*token)->key)))
		return (1);
	else if ((*token)->key == l_dollar)
		return (1);
	else if ((*token)->key == l_til)
		return(1);
	else
		return (0);	
}

/* if token->next is no word or DOLLAR or Til */
char		min_dollar(t_lexer **token, t_expander **word, t_expander **extra, t_exphelp help)
{
	if ((*token)->value[0] == E_QUOTE)
		help.export = 1;
	(*token) = (*token)->next;
	if (ft_next_is_special(token))
		return (ft_special_next_token(token, word, extra, help));
	else if ((*token)->key == l_asterisk)
	{	
                *token = (*token)->next;
                return (help.space);
	}	
	else
		return (min_eval_dollar(token, word, extra, help));
}
