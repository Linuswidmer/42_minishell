/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:55:26 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/11 11:01:39 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/04/09 22:09:45 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <stdlib.h>


typedef enum 
{
	l_empty,
	l_dquote,
	l_quote,
	l_word,
	l_asterisk,
	l_paraopen,
	l_paraclose,
	l_heredoc,
	l_append,
	l_in,
	l_out,
	l_dollar,
	l_and,
	l_or,
	l_semi,
	l_pipe,
	l_escape,
	l_amp,
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
char	*ft_substr(char const *s, unsigned int start, size_t len);

t_lexertype check_token(char c, char next);

t_lexer *lexer(char *input);

// int check_token_list(t_lexer *token);

int parse_dollar(char *input, int pos, t_lexer *tmp, int start);
int parse_quote(char *input, int pos, t_lexer *tmp, int start, t_lexertype token);
int parse_double_tokens(char *input, int pos, t_lexertype current_token, t_lexer *tmp);
int parse_single_tokens(t_lexer *tmp, t_lexertype current_token, int pos);
int parse_word(char *input, int pos, t_lexer *tmp, int start);
int parse_token_to_list(t_lexertype current_token, char *input, int pos, t_lexer *tmp, int start);

void expand_dollar_tokens(t_lexer *first);

void free_token_list(t_lexer *token_list);

int skip_space_tab(char *input, int pos);
t_lexer *init_lexer_struct();
void print_token_list(t_lexer *first);
#endif
