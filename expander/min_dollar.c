/* *****************************ft_strjoin(old, "123")********************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:00:43 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/12 16:22:29 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char *ft_status(char *old)
{
char *status;
char *temp;
temp = ft_itoa(g_status);
status = ft_strjoin(old, temp);
//min_free(temp);
return (status);
}



static  char    *ft_dollar_in_dict(char *dollar, char *old,  t_dict *dict)
{
char *temp; 

if (*dollar == QUESTION)
	return (ft_status(old));
if (*dollar == E_SPACE)
{
	temp = ft_strjoin(old, DOLLAR);
	dollar = ft_strjoin(temp, dollar);
	//min_free(temp);
	return (dollar);
}
if (*dollar == SUB)
	ft_putstr_fd(ERR_SUB, 2);	
while (dict)
{
	if (ft_strncmp(dict->key, dollar, ft_strlen(dollar)))
		dict = dict->next_entry;
	else
		 break;
}
if (!dict)
   return (old);
else
	return (ft_strjoin(old, dict->value));
}




static char	*ft_dollar(t_lexer **token, char *temp, t_dict *dict)
{
char *new;

*token = (*token)->next;
if (!*token || !min_token_is_word((*token)->key))
{	
	if (!temp)
		new = ft_strdup(DOLLAR);	
	else 
		new = ft_strjoin(temp, DOLLAR); 
}	
else if ((*token)->key == l_dollar)
{	
	//min_print_error(PRECESSID, 0); 
	new = temp;
}
else if ((*token)->key == l_til)
	new = ft_strjoin(temp, TIL);
else
	new = ft_dollar_in_dict((*token)->value, temp, dict); 
if (*token)	
	*token = (*token)->next;
return (new);
}


void min_dollar(t_lexer **token, t_expander **word, t_expander  **extra,  t_dict *dict)
{
    t_expander  *end;
    char *temp;

    if ((*word)->key == l_empty)
    {   
        (*word)->key = l_word;
        end = *word;
    }   
    else
    {   
        end = min_last_expander(*word); 
        end->next = min_init_expander(l_word);
        end = end->next;
           
    }   
    if (end)
    {   
		temp = end->word; 
		end->word = ft_dollar(token, temp, dict); 
		//min_free(temp);
	}	
	if (!end || !end->word)
        min_free_expander(word);
}
