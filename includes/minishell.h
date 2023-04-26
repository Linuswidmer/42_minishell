/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:20:37 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/07 17:57:11 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int min_status;

#include "libft.h"
#include "structs.h"
#include "lexer.h"
#include "typedef.h"
#include "init.h"
#include "builtins.h"
#include "free.h"

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <fcntl.h>
#include <readline/history.h>

# endif
