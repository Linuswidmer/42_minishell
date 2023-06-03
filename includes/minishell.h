/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:20:37 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/08 12:44:07 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int g_status;

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <fcntl.h>
#include <readline/history.h>
#include <dirent.h>
#include <sys/wait.h>


#include "typedef.h"
#include "define.h"
#include "structs.h"
#include "macros.h"
#include "libft.h"
#include "lexer.h"
#include "init.h"
#include "parser.h"
#include "builtins.h"
#include "free.h"
#include "expander.h"
#include "job.h"
#include "pipe.h"	
#include "executer.h"
#include "free.h"
#include "error.h"	


# endif
