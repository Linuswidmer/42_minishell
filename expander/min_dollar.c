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

/*
static	int ft_add_to_back(t_expander *word, char *value, char space)
{
	t_expander  *end;
	
	char *temp;

	
	
	if (word->key == l_empty space)
    {
        word->key = l_word;
        end = word;
    }
    else
    {
        end = min_last_expander(word);
    }
    if (end)
    {	
			if (!space)
        		temp = end->word;
        		end->word = ft_strjoin( temp, (*token)->value);
        		min_free(&temp);
				
	
    }
    if (!end->word)
        min_free_expander(&word);		



			

	return (0);
}
*/


static char *ft_status(char *word)
{
	char *status;
	char *temp;
	temp = ft_itoa(g_status);
	status = ft_strjoin(temp, word);
	min_free(&temp);
	return (status);
}


static int 	ft_check_word(char *word, char **result)
{
	*result = NULL;
	if (!word)	
		return (0); 	
	else if (ft_isdigit(word[0]))
		*result = ft_strdup(++word);
	else if (ft_isalpha(word[0]))
	{
		*result = ft_strdup(word);
		return (1);
	}
	else if (word[0] == QUESTION)
		*result = ft_status(++word);	
	else 
	{
		if (word[0] == SUB)
			ft_putstr_fd(ERR_SUB, 2);
		*result = ft_strjoin(DOLLAR, word);
	}
	return (0);
}

static char	ft_add_value_to_expander(t_lexer **token, t_expander **word, char **result, char space)
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


static	int	ft_check_dict(char **dollar, char **value,  t_dict *dict)
{	
	while (dict)	
	{
		if (ft_strncmp(dict->key, *dollar, ft_strlen(*dollar)))
                	dict = dict->next_entry;
		else
                	 break;
	}
	min_free(dollar);
	if (!dict)
		return (0);
	*value = ft_strdup(dict->value);
	return (1);
}
		



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
		




/* eval entry dict  and return if end with space if last ist asterisk return 3*/

static char	ft_eval_splitvalue( t_expander **word, t_expander **extra, t_exphelp help, char **splitvalue)
{
	int len;
	int n;

	len = ft_len_split(splitvalue);		
	n = -1;
	while (word && splitvalue[++n])
	{
		
		if (ft_check_for_asterisk(splitvalue[n]))
		{	
			
			if (!n && n == len -1 && !help.space)
				return (3);
			else if (n == len -1 && !help.space)
			{
				return (4);
			}	  
			else if (!n && (!help.space || help.space == 2))
			{	
				min_asterisk(NULL, word, ft_asterisk_splitvalue(splitvalue[n]), min_init_exphelp(help.dict, 1 ,1));
			}
			else if (extra)
				 min_asterisk(NULL, extra, ft_asterisk_splitvalue(splitvalue[n]), min_init_exphelp(help.dict, 0 ,1));
			else		
				min_asterisk(NULL, word, ft_asterisk_splitvalue(splitvalue[n]),  min_init_exphelp(help.dict, 0 ,1));
			
		}	
		else
		{
			if (extra)		
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
				{
					min_word(NULL, extra, splitvalue[n], 1);
				}
			}
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
		if (!n && (help.space == 1 || help.space == 3))
			help.space--;
	}
	return (help.space);
}
	

 


static char	ft_dollar(t_lexer **token, t_expander **word, t_expander **extra, t_exphelp help)
{
	char *dollar_value;
	char *value;
	char **splitvalue;
		
       /* check first special caracter */
	if (!ft_check_word((*token)->value, &dollar_value))
		return (ft_add_value_to_expander(token, word, &dollar_value, help.space));
	/* check word in dict */
	if (!ft_check_dict(&dollar_value, &value, help.dict))
	{	
		if (*token)
			*token = (*token)->next;
		return (help.space);
	}
	/* export && qoute mode */
	if ( help.export)	
		return(ft_add_value_to_expander(token, word, &value, help.space)); 
	splitvalue = ft_delimiter_split(value, &help.space, E_SPACE);
	min_free(&value);
	if (!splitvalue)
		return (ft_add_value_to_expander(token, word, NULL, help.space));
	help.space = ft_eval_splitvalue(word, extra, help, splitvalue);
	if (help.space == 3)
		help.space = min_asterisk(token, word, ft_asterisk_splitvalue(splitvalue[ft_len_split(splitvalue) -1]), min_init_exphelp(help.dict, 1, 0));
	if (help.space == 4)
	{
		if (extra)
		{
			help.space = min_asterisk(token, extra, ft_asterisk_splitvalue(splitvalue[ft_len_split(splitvalue) -1]), min_init_exphelp(help.dict, 0, 1));
		}
		else
			help.space = min_asterisk(token, word, ft_asterisk_splitvalue(splitvalue[ft_len_split(splitvalue) -1]), min_init_exphelp(help.dict, 0, 1));
}
	//min_doublefree(&splitvalue);
	if (*token)
		*token = (*token)->next;
	return (help.space);
}




/* if token->next is no word or DOLLAR or Til */
char		min_dollar(t_lexer **token, t_expander **word, t_expander **extra, t_exphelp help)
{
	if ((*token)->value[0] == E_QUOTE)
		help.export = 1;
	(*token) = (*token)->next;
	if (!(*token) || (*token && !min_token_is_word((*token)->key)))
	{
		min_word(NULL, word, DOLLAR, help.space);
		return (1);
	}	
	else if ((*token)->key == l_dollar)
	{
		ft_putstr_fd(ERR_ID, 2);
		return (min_word(token, word, DDOLLAR, help.space));
	}	
	else if ((*token)->key == l_til)
		return (min_word(token, word, DTIL, help.space));
	else if ((*token)->key == l_asterisk)
	{	
	        if (*token)
                        *token = (*token)->next;
                return (help.space);
	}	
	else
		return (ft_dollar(token, word, extra, help));
}
