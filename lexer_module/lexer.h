/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:55:26 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/01 17:50:54 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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

#endif
