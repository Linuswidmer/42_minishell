# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 09:41:35 by lwidmer           #+#    #+#              #
#    Updated: 2023/04/07 12:15:48 by lwidmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILENAMES_LEXER = lexer utils tokens check_token_list lexer_parser expander lexer_utils 

FILENAMES_MS = main

LEXER_SRCS_DIR = ./src_lexer/
LEXER_OBJS_DIR = ./src_lexer/

MS_SRCS_DIR = ./src/
MS_OBJS_DIR = ./src/

SRCS_LEXER = $(addprefix $(LEXER_SRCS_DIR), $(addsuffix .c, $(FILENAMES_LEXER)))
OBJS_LEXER= $(addprefix $(LEXER_OBJS_DIR), $(addsuffix .o, $(FILENAMES_LEXER)))

SRCS_MS = $(addprefix $(MS_SRCS_DIR), $(addsuffix .c, $(FILENAMES_MS)))
OBJS_MS= $(addprefix $(MS_OBJS_DIR), $(addsuffix .o, $(FILENAMES_MS)))

SRCS = $(SRCS_LEXER) ${SRCS_MS}
OBJS = $(OBJS_LEXER) ${OBJS_MS}
INCLUDES_DIR = -I./includes/ -I./src_lexer


${NAME}: ${OBJS}
	cc -o ${NAME} $^ -lreadline

.c.o: ${SRCS}
	cc -c -o $@ $< ${INCLUDES_DIR}
test:
	echo ${SRCS}
