/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:51:43 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/05 16:51:45 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# ifndef _DEBUG1	
#  define _DEBUG1 1	
# endif

# ifndef _DEBUG    
#  define _DEBUG 1 
# endif

# define EMPTY ""
# define ASTERISK "*"
# define DOLLAR "$"
# define QUESTION '?'	
# define E_SPACE	' '
# define TIL "~" 
# define SUB '('
# define ERR_SUB "$() not implemented.\n"  
# define CURRDIR "./"
# define HEREDOC "temp"	
# define HEREDOC_PATH "/tmp/"
# define HOME "HOME"

#endif
