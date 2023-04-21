# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 09:41:35 by lwidmer           #+#    #+#              #
#    Updated: 2023/04/21 11:34:37 by lwidmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

REMOVE = rm -f

FILENAMES_LEXER = lexer tokens check_token_list lexer_parser expander lexer_utils utils 

FILENAMES_PARSER = min_parser_error min_set_file_io min_token_is_para min_jobnode	min_parser_malloc_fail min_set_io min_token_is_route min_last_cmdnode min_pipenode min_subnode min_token_is_word min_last_ionode min_routenode min_token_is_io min_parser min_set_cmd min_token_is_io_in min_debug 

FILENAMES_MS = main

LEXER_SRCS_DIR = ./src_lexer/
LEXER_OBJS_DIR = ./src_lexer/

PARSER_SRCS_DIR = ./parser/
PARSER_OBJS_DIR = ./parser/

MS_SRCS_DIR = ./src/
MS_OBJS_DIR = ./src/


SRCS_LEXER = $(addprefix $(LEXER_SRCS_DIR), $(addsuffix .c, $(FILENAMES_LEXER)))
OBJS_LEXER = $(addprefix $(LEXER_OBJS_DIR), $(addsuffix .o, $(FILENAMES_LEXER)))

SRCS_PARSER = $(addprefix $(PARSER_SRCS_DIR), $(addsuffix .c, $(FILENAMES_PARSER)))
OBJS_PARSER = $(addprefix $(PARSER_OBJS_DIR), $(addsuffix .o, $(FILENAMES_PARSER)))


SRCS_MS = $(addprefix $(MS_SRCS_DIR), $(addsuffix .c, $(FILENAMES_MS)))
OBJS_MS= $(addprefix $(MS_OBJS_DIR), $(addsuffix .o, $(FILENAMES_MS)))

SRCS = $(SRCS_LEXER) ${SRCS_MS} ${SRCS_PARSER}
OBJS = $(OBJS_LEXER) ${OBJS_MS} ${OBJS_PARSER}
INCLUDES_DIR = -I./includes/ -I./src_lexer -I./parser


${NAME}: ${OBJS}
	cc -o ${NAME} $^ -lreadline -L. ./libft/libft.a

.c.o: ${SRCS}
	cc -c -o $@ $< ${INCLUDES_DIR}

lib:
	make -C ./libft

clean:
	$(REMOVE) $(OBJS)
	$(REMOVE) $(NAME)

libclean: 
	make fclean -C ./libft




