/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:43:28 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/26 15:13:49 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


static char *ft_find_filename(char *heredoc)
{

	char *path;
	char *temp;

	path = ft_strdup(heredoc);
	//printf("%s\n", path);	
	//printf("%i\n", access(path, F_OK));			
	while (!access(path, F_OK))
	{
		temp = path;
		path = ft_strjoin(path, "1");
		//printf("%s\n", path);
		//min_free(temp);
		//min_free(num);
	}
	return (path);
}

				
static char *ft_get_limiter(t_lexer *token)
{
	char *limiter;
	char *temp;
	
	limiter = ft_strdup(EMPTY); 
	while (token && token->key == l_space)
		token = token->next;
	if (limiter && token && min_token_is_word(token->key))
	{
		while (limiter && token && min_token_is_word(token->key))
		{
			temp = limiter;
			if (min_token_is_word(token->key) == 2)
				limiter = ft_strjoin(limiter, DOLLAR);
			else if(min_token_is_word(token->key) == 3)
				limiter =ft_strjoin(limiter, ASTERISK);
			else 
				limiter = ft_strjoin(limiter, token->value);
			//min_free(&temp);		
			token = token->next;
		}
		return (limiter);			
	}
	else
		return (NULL);
}	
	
/* set path to next next wrd and delete the others*/
static t_lexer	*ft_set_file(t_lexer *token,char *path)
{

	t_lexer *file;
	char	*old;

	file = token->next;
	old = token->value;
	token->key = l_word;
	token->value = path;
	//min_free(&old);
	
	while (file && file->key == l_space)
	{	
		if (file->next)
			file = file->next;
			//min_free_lexer_node(&file->prev);
		//else
			//min_free_lexer_node(&file);
	}
	while (file && min_token_is_word(file->key))
	{
            file = file->next;
            //min_free_lexer_node(&file->prev);
        //else
            //min_free_lexer_node(&file);
	}
	token->next = file;
	if (file)
		file->prev = token;
	return (token);
}

int	min_heredoc(t_lexer **token, char *heredoc)
{
	char	*path;
	int		fd;
	char	*line;
	char	*limiter;
	
//	printf("start heredoc\n");	

	path = ft_find_filename(heredoc);
	//printf("%s\n", path);
	if (!path)
		return (1);
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	limiter = ft_get_limiter((*token)->next);
	//printf("%s\n", limiter);
	if (fd != -1 && limiter)
	{
		while(1)
		{
			write(1, "heredoc :", 10);
			line = get_next_line(0);
			if (!line)
			{
				printf("EOF\n");
				//min_print_error(ENDOFFILE);
				break;
			}	
			if (ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
			{
				//min_free(&line)
				break;
			}
			write(fd, line, ft_strlen(line));
			//min_free(&line);
		}
		*token = ft_set_file((*token)->next, path);
		//min_free(&path);
		if (close(fd))
			return (1);
		return (0);
	 }
	//min_print_error(HEREDOC);
	return (1);
}		
