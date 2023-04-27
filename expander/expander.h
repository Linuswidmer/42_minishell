/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:27:39 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/24 12:40:14 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexer.h"
# include <stdlib.h>
# include "libft.h"
# include <dirent.h>
# include <stdio.h>
# include <sys/types.h>


# define DOLLAR "$"
# define EMPT ""	
# define E_SPACE	" "
# define ERR_SUB "$() not implemented.\n"  
# define CURRDIR "./"


typedef struct s_expandjob    t_expandjob;
typedef struct s_cmdnode    t_cmdnode;
typedef struct s_ionode     t_ionode;
typedef struct s_expander     t_expander;
typedef struct s_dollar     t_dollar;

struct s_expandjob
{
    t_cmdnode   *cmd;
    t_ionode    *in;
    t_ionode    *out;
};

struct s_cmdnode
{
    char    *arg;
    t_cmdnode *next;
};

struct s_ionode
{
    t_lexertype value;
    char *file;
    t_ionode *next;
};

struct s_expander
{
    t_lexertype key;
    char    *word;
    t_expander *next;
};

struct s_dollar
{
	t_lexertype value;
	char	*word;
	t_dollar *next;
//	t_ast	*ast;
};

/* functions */



t_lexer *min_set_file_io(t_ionode **end, t_lexer *token, t_dict *dict);
t_lexer *min_set_io(t_lexer *token, t_expandjob **job, t_dict *dict);


t_expandjob *min_expander(t_lexer *token, t_dict *dict, t_lexer *end);





#endif
