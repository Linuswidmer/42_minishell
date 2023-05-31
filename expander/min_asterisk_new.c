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






/* this can also handel if * are in $cmd  */
static void	ft_start_asterisk(char *word, t_expander **asterisk, t_expander *old)
{
		if ( word)
		{
			*asterisk = min_init_expander(l_word, word);
			if (*asterisk)
			{ 	
				if (old)
					(*asterisk)->next = old;
				else
				{
					(*asterisk)->next = min_init_expander(l_asterisk, NULL);
						if (!(*asterisk)->next)
							min_free_asterisk(asterisk);
				}
			}	
		}
		else if (old)
			 *asterisk = old;
		else	
			*asterisk = min_init_expander(l_asterisk, NULL);
	}
}


static void ft_word(t_lexer **token, t_expander *asterisk, char *value)
{
	t_expander  *end;
	
	 end = min_last_expander(asterisk);
	if (end->key == l_asterisk)
	{
		end->next = min_init_expander(l_word, EMPTY);
		if (!end->next)
		{
			min_free_expander(asterisk);
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

static char	ft_dollar(token, asterisk, extra, dict)		
{
	char		space;
	t_expander	*dollar;
	t_epander 	*end;	


	space = min_dollar(token, &dollar, extra , dict);
	if (!dollar)
		min_free_expander(asterisk);
	else
	{
		end = min_last_expander(*asterisk);
		end->next = dollar;
	}
	return (space);
}

static	void	ft_asterisk(t_lexer **token, t_expander **asterisk)
{
	
	t_expander  *end;

	end = min_last_expander(*asterisk);
	end->next = min_init_expande(l_asterisk, NULL);
	if (!end->next)
		min_free_asterisk(asterisk);
	*token = (*token)->next;
		
}

static char	ft_get_all_asterisk_members(t_lexer **token, t_expander **asterisk, t_expander **extra, t_dict *dict)
{
	char	space;
	
	space = 0;
	*extra = NULL;
	while (space && !*extra && asterisk && *token && min_token_is_word((*token)->key))
	{
		if (min_token_is_word((*token)->key) == 1)
            		ft_word(token, asterisk, NULL);
		else if (min_token_is_word((*token)->key) == 2)
			space = ft_dollar(token, asterisk, extra, dict);
		else if ( min_token_is_word((*token)->key) == 4)
			ft_word(token, asterisk, TIL);
		else
			ft_asterisk(asterisk);
	}
	return (space);
}




/* ???? */
char	min_asterisk(t_lexer **token, t_expander **word, char to, char wo, t_expander *old, t_dict *dict)
{
	t_expander	*asterisk;
	t_expander	*extra;	
	char		space;

	if (!*word)	
		return (1);
	space = 1;
		
	if (wo)
		ft_start_asterisk((*word)->word, &asteriski, old);
	else
		ft_start_asterisk(NULL, &asterisk, old);
	if (!to)
		min_evaluate_asterisk(word, asterisk, wo);
	else
	{
		space = ft_get_all_asterisk_members(token, &asterisk, &extra, dict);
		min_evaluate_asterisk(word, asterisk);
		min_add_extra_to_word(word, extra)
	}
	if (!asterisk)
		min_free_expander(word);
	min_free_asterisk(&asterisk);
	return (space);	
}

