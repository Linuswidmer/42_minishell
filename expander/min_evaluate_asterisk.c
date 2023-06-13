
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

static int	ft_word_in_filename(char **filename, char *word, t_expander *curr)
{
	if (!**filename)
		return (0);
	while(**filename && *word)
	{ 
		if (*(*filename)++ != *word++)
			return (0);
	}
	if (!**filename && !*word)
			return (1);
	if (!*word && curr->next)
			return (1);
	else			
			return (0);
}
	
static void ft_move_filename_to_word(char **filename, t_expander *word)
{
	while (**filename && **filename != (word->word)[0])
		(*filename)++;
//	printf("word: %s, filename %s \n", word->word, *filename);
}

static int	ft_last_word(char *filename, char *word)
{
	int lena;
	int lenb;
	
		
	lena = (int)ft_strlen(filename) -1;
	lenb = (int)ft_strlen(word) -1;
	
	if(!*filename)
		return (0); 
			
	while (lena >= 0 && lenb >= 0)
	{
		if (filename[lena] == word[lenb])
		{
		//	ft_printf_fd(" %c [%i]// %c [%i]\n", 2, filename[lena], lena, word[lenb], lenb);
			lena--;
			lenb--;
		}
		else
			return (0);
	}
	return (1);
		  	
}




int	ft_fit_to_asterisk(char *filename, t_expander *word)
{
	char first;
	
	first = 0;
	while (word && filename)
	{
		if(word->key == l_asterisk)
		{
			if (!first++)
			{
				if (*filename == '.')	
					return (0);
			}
			while (word->key == l_asterisk)
			{
				if (!word->next)
					return (1);
				word = word->next; 
			}
			ft_move_filename_to_word(&filename, word);
		}	
		else if (word->key == l_word )
		{ 
			first++;
			if ( !word->next)
			{
				if (!ft_last_word(filename, word->word))
					return (0);
				else 
					return (1);
			}	
			if (!ft_word_in_filename(&filename, word->word, word))
				return (0);
			word = word->next;
		}
		else
			word = word->next;
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
