/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_asterisk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 08:50:43 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/17 11:21:52 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void ft_free_values(char ***values)
{
	(void)values;
}

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
	while (word && *filename)
	{
		if(word->key == l_asterisk)
		{
			if (!first++)
			{
				if (*filename == '.')
					return (0);
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
				return (0);	
			else
				word = word->next;
		}
	}	
	return (1);
}

int	ft_count_values(t_expander *word)
{
	int             counter;
	struct dirent   *d;
	DIR             *dh;

    dh = opendir("./");
    d = readdir(dh);
	counter = 0;
	while (d) 
    {   
        if (ft_fit_to_asterisk(d->d_name, word))
			counter ++;
		d = readdir(dh);
	}	
	free (dh);
	return (counter);
}


char 	**min_asterisk(t_expander *word)
{
	char			**values;
	int				counter;
	struct dirent	*d;
    DIR 			*dh;

	counter = ft_count_values(word);
	values = (char **)malloc(sizeof(values) * (counter + 1));
	dh = opendir("./");
	d = readdir(dh);
	counter = 0;
	while (d && values)
	{
		if (ft_fit_to_asterisk(d->d_name, word))
		{
			values[counter] = ft_strdup((const char *)d->d_name);
			if (!values[counter++])
					ft_free_values(&values);
		}			
		d = readdir(dh);
	}
	if (values)
		values[counter] = NULL;
	free (dh);
	return (values);
}
