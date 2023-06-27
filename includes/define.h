/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:51:43 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/27 13:53:15 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/06/27 12:51:12 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define _DEBUG 0 
# define _DEBUG1 0

/* PARSER*/
# define P_NEWLINE "newline"

# define EMPTY ""
# define ASTERISK "*"
# define DOLLAR "$"
# define QUESTION '?'	
# define E_SPACE	' '
# define E_ASTERISK '*'	
# define TIL "~" 
# define SUB '('
# define ERR_SUB "$() not implemented.\n"
# define ERR_MALL "MALLOC FAIL IN ASTERISK EVAL.\n"	  
# define ERR_ID	"$$ not implemented.\n"
# define CURRDIR "./"
# define DDOLLAR  "$$"
# define DTIL	"$~"
# define E_QUOTE 'q'	

/* HEREDOC*/
# define HEREDOC "temp"	
# define HEREDOC_PATH "/tmp/"
# define HERETXT "heredoc :"	
# define HERENUM "1"	
# define HEREDOC_EVAL "b"
# define HEREEOF "EOF\n"
# define HEREFAIL "HEREDOC FAIL\n"	

/* EXPANDER*/
# define TMOPEN "* ambiguous redirect\n"	

# define HOME "HOME"
#endif
