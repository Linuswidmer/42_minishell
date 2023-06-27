/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:28:09 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/27 12:11:01 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/* PARSER*/
# define APPEND ">>"
# define IN "<"
# define OUT ">"
# define ASTERISK "*"
# define PARAOPEN "("
# define PARACLOSE ")"
# define L_HEREDOC "<<"
# define L_AND "&&"
# define L_OR "||"
# define L_SEMI ";"
# define L_PIPE "|"
# define L_TIL "~" 

int	min_parser_error(t_ast **ast, t_lexertype key, char *value);
#endif
