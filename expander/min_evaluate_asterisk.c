/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_asterisk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 08:50:43 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/12 16:22:53 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_word_in_filename(char *filename, char *word, t_expander *curr)
{
	if (!*filename)
		return (0);
	while(*filename && *word)
	{ 		
		if (*filename++ != *word++)
			return (0);
	}
	if (!*filename && !*word)
			return (1);
	if (!*word && curr->next)
			return (1);
	else			
			return (0);
}
	
t_expander	*ft_move_filename_to_word(char **filename, t_expander *word)
{
	t_expander *next;

	next = word->next;
	while (**filename && **filename != (next->word)[0])
		(*filename)++;
	return (next);
}

int	ft_fit_to_asterisk(char *filename, t_expander *word)
{
	char first;
	
	first = 0;
	while (word && filename)
	{
	//printf("%s\n", filename);				
		if(word->key == l_asterisk)
		{
			if (!first++)
			{
				//	printf("%s\n", filename);
				if (*filename == '.')
				{	
//					printf("%s\n", filename);
					return (0);
				}
			}
			if (!word->next)
				return (1);
			else
				word = ft_move_filename_to_word(&filename, word);
		}	
		if(word->key == l_word )
		{ 
			first++;
			if (!ft_word_in_filename(filename, word->word, word))
			{
//				printf("%s\n", filename);
				return (0);
			}	
			else
				word = word->next;
		}
	}	
	return (1);
}
static char *ft_notfound(t_expander *asterisk)
{
        
        char *value;
        char *temp;


        value = ft_strjoin(EMPTY, EMPTY);
        while (value && asterisk)
        {
                temp = value;
                if (asterisk->key == l_asterisk)
                        value =  ft_strjoin(temp, ASTERISK);
                else    
                        value = ft_strjoin(temp, asterisk->word);
                min_free(&temp);
                asterisk = asterisk->next;
        }
        return (value);
}

void 	min_evaluate_asterisk(t_expander **word, t_expander *asterisk, char wo)
{
	struct dirent	*d;
    DIR 			*dh;
	char			found;
	t_expander		*end;
	
	dh = opendir("./");
	d = readdir(dh);
	found = 0;

	while (d)
	{
		if (ft_fit_to_asterisk(d->d_name, asterisk))
		{
			//printf("%s\n", d->d_name);	
			found = 1;
			if (min_addlast_expander(word, d->d_name, &wo))
				break ;
		}			
		d = readdir(dh);
	}
	if (!found)
		min_addlast_expander(word, ft_notfound(asterisk), &wo);
	free (dh);
}
