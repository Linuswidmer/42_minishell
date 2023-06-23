/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:51:43 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/23 16:11:20 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# ifndef _DEBUG1	
#  define _DEBUG1 0	
# endif

# ifndef _DEBUG    
#  define _DEBUG 0 
# endif

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
#define TMOPEN "* ambiguous redirect\n"	

# define HOME "HOME"
#endif
