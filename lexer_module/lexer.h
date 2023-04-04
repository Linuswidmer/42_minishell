/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:55:26 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/04 12:58:42 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


typedef enum 
{
	EMPTY,
	DQUOTE,
	QUOTE,
	WORD,
	ASTERISK,
	PAROPEN,
	PARCLOSE,
	HEREDOC,
	APPEND,
	IN,
	OUT,
	DOLLAR,
	AND,
	OR,
	SEMI,
	PIPE,
	ESCAPE,
} t_lexertype ;	

typedef struct s_lexer 
{
	t_lexertype key;
	char *value;
	struct s_lexer *next;
	struct s_lexer *prev;
} t_lexer;

size_t  ft_strlen(const char *str);
size_t  ft_strlcpy(char *dest, const char *src, size_t size);
char    *ft_strdup(const char *s);
int	ft_isalnum(int c);

t_lexertype check_token(char c, char next);

int check_token_list(t_lexer *token);


#endif
