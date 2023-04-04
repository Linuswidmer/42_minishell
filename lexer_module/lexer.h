/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:55:26 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/04 15:48:58 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum 
{
	empty,
	dquote,
	quote,
	word,
	asterisk,
	paropen,
	parclose,
	heredoc,
	append,
	in,
	out,
	and,
	or,
	semi,
	pipe,
	escape,
} t_lexertype ;	

typedef struct s_lexer 
{
	t_lexertype key;
	char *value;
	struct s_lexer *next;
	struct s_lexer *prev;
} t_lexer;

#endif
