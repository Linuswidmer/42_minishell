/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_asterisk_new.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:59:48 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/12 16:14:00 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
static int	ft_is_asterisk(t_expander *word)
{
	while (word && word->key != l_asterisk)
		word = word->next;
	if (!word)
		return (0);
	else
		return (1);
}


static  void ft_check_last_asterisk_entry(t_expander **old,   t_expander *word)
{      
        char            *oldword;
	t_expander	*temp;	

        if ((*old)->key == l_word && (word && (min_last_expander(word))->key == l_word))
        {
                oldword = (*old)->word;
                (*old)->word = ft_strjoin((min_last_expander(word))->word, oldword);
                min_free(&oldword);
        }
	else
	{
		temp = *old;
		if (!ft_is_asterisk(word))
		{	
			*old = min_init_expander((min_last_expander(word))->key, (min_last_expander(word))->word);	
		}
		else
			*old = word;	
		if (*old)
			(min_last_expander(*old))->next = temp;		
	} 		
}




/* this can also handel if * are in $cmd  */
static void	ft_start_asterisk(t_expander *word, t_expander **asterisk, t_expander *old)
{
		if ( word)
		{
			if (!old)
			{	
				 *asterisk = min_init_expander(l_word, word->word);
				if (*asterisk)
					(*asterisk)->next = min_init_expander(l_asterisk, NULL);
				
			}
			else

			{
				ft_check_last_asterisk_entry(&old, word);
				*asterisk = old;
			
			}	
		}
		else if (old)
			 *asterisk = old;
		else	
			*asterisk = min_init_expander(l_asterisk, NULL);	
}


static void ft_word(t_lexer **token, t_expander **asterisk, char *value)
{
	t_expander	*end;
	char		*temp;
	
	 end = min_last_expander(*asterisk);
	if (end->key == l_asterisk)
	{
		end->next = min_init_expander(l_word, EMPTY);
		if (!end->next)
		{
		//	min_free_expander(asterisk);
		}	
		else
			end = end->next;
	}
	temp = end->word;
	if (!value)
		end->word = ft_strjoin( temp, (*token)->value);
	else
		end->word = ft_strjoin( temp, value);
	min_free(&temp);
	*token = (*token)->next;
}


/* decide t_exphelp   */
static char	ft_dollar(t_lexer **token, t_expander **asterisk, t_expander **extra, t_dict *dict)		
{
	t_expander	*dollar;
	t_expander 	*end;
	t_exphelp	help;		
	
	dollar = *asterisk;
	help = min_init_exphelp(dict, 0, 0);
	help.space = min_dollar(token, &dollar, extra , help);
	if (!dollar)
		min_free_expander(asterisk);
	else
		*asterisk = dollar;
	return (help.space);
}

static	void	ft_asterisk(t_lexer **token, t_expander **asterisk)
{
	
	t_expander  *end;

	end = min_last_expander(*asterisk);
	end->next = min_init_expander(l_asterisk, NULL);
	//	if (!end->next)
	//	min_free_asterisk(asterisk);
	*token = (*token)->next;
		
}

static char	ft_get_all_asterisk_members(t_lexer **token, t_expander **asterisk, t_expander **extra, t_dict *dict)
{
	char	space;
	
	space = 0;
	*extra = min_init_expander(l_empty, EMPTY);
	if (!extra)
		return (space);
		
	while (!space && (*extra)->key == l_empty && asterisk && *token && min_token_is_word((*token)->key))
	{
		if (min_token_is_word((*token)->key) == 1)
            		ft_word(token, asterisk, NULL);
		else if (min_token_is_word((*token)->key) == 2)
			space = ft_dollar(token, asterisk, extra, dict);
		else if ( min_token_is_word((*token)->key) == 4)
			ft_word(token, asterisk, TIL);
		else
			ft_asterisk(token, asterisk);
	}
	return (space);
}




/* creates a link list with all asterisk  and evaluate it, if $ have more then one value gives back the zhe other values in extra  
help.word -> flag to show that before first apperace of * was an other word 
help.token -> flag to show if token can be used 
t_expander *old -> get the evaluatetet link list from a * in a $ARG 
-> this will be connectet to the fromer Asterisk or get evaluatett alone or with the next tokens */
char	min_asterisk(t_lexer **token, t_expander **word, t_expander *old, t_exphelp help)
{
	t_expander	*asterisk;
	t_expander	*extra;	
	                                
	if (!*word)	
		return (1);
	if ((!help.space && (min_last_expander(*word))->key == l_word) || help.word)
		ft_start_asterisk(*word, &asterisk, old);
	else	
		ft_start_asterisk(NULL, &asterisk, old);
	if ((!help.space && (min_last_expander(*word))->key == l_word) || (*word)->key ==l_empty)
		help.word = 1; 
	if (!token && asterisk)
	{
		min_evaluate_asterisk(word, asterisk, help.word);
	}
	else if (asterisk)
	{
		*token = (*token)->next;
		help.space = ft_get_all_asterisk_members(token, &asterisk, &extra, help.dict);
		min_evaluate_asterisk(word, asterisk, help.word);
		min_add_extra_to_word(word, extra);
	}
	//	if (!asterisk)
	//	min_free_expander(word);
	//min_free_expander(&asterisk);
	//min_free_expander(&extra);
	return (help.space);	
}

