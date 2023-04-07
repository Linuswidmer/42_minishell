# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 09:41:35 by lwidmer           #+#    #+#              #
#    Updated: 2023/04/07 11:54:28 by lwidmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILENAMES_LEXER = lexer utils tokens check_token_list lexer_parser expander 

LEXER_SRCS_DIR = ./src_lexer/
LEXER_OBJS_DIR = ./src_lexer/

SRCS_LEXER = $(addprefix $(LEXER_SRCS_DIR), $(addsuffix .c, $(FILENAMES_LEXER)))
OBJS_LEXER= $(addprefix $(LEXER_OBJS_DIR), $(addsuffix .o, $(LEXER_FILENAMES)))

SRCS = $(SRCS_LEXER)
OBJS = $(OBJS_LEXER)

${NAME}: ${OBJS}
    cc -o ${NAME} $^ -lreadline

.c.o: ${SRCS}
    cc -c -o $@ $<

