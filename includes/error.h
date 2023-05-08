/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:28:09 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/08 13:27:07 by jstrotbe         ###   ########.fr       */
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






void    min_parser_error1(t_ast **ast, t_lexertype key, char *value);




#endif
