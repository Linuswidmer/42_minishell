# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 09:41:35 by lwidmer           #+#    #+#              #
#    Updated: 2023/04/26 14:45:16 by lwidmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

REMOVE = rm -f

FILENAMES_LEXER = lexer tokens check_token_list lexer_parser lexer_utils free_lexer token_list_utils \
				dollar_postprocessing

FILENAMES_PARSER = min_parser_error  min_token_is_para min_jobnode	min_parser_malloc_fail  min_token_is_route min_pipenode min_subnode min_token_is_word  min_routenode min_token_is_io min_parser  min_token_is_io_in min_debug min_heredoc_fail min_free_ast min_heredoc

FILENAMES_MS = main

FILENAMES_INIT = signals init dict free_dict_builtins_min builtins builtins_wrapper

FILENAMES_BUILTINS = cd echo env exit export pwd unset

LEXER_SRCS_DIR = ./src_lexer/
LEXER_OBJS_DIR = ./src_lexer/

PARSER_SRCS_DIR = ./parser/
PARSER_OBJS_DIR = ./parser/

MS_SRCS_DIR = ./src/
MS_OBJS_DIR = ./src/

INIT_SRCS_DIR = ./init/
INIT_OBJS_DIR = ./init/

BUILTINS_SRCS_DIR = ./init/builtins/
BUILTINS_OBJS_DIR = ./init/builtins/


SRCS_LEXER = $(addprefix $(LEXER_SRCS_DIR), $(addsuffix .c, $(FILENAMES_LEXER)))
OBJS_LEXER = $(addprefix $(LEXER_OBJS_DIR), $(addsuffix .o, $(FILENAMES_LEXER)))

SRCS_PARSER = $(addprefix $(PARSER_SRCS_DIR), $(addsuffix .c, $(FILENAMES_PARSER)))
OBJS_PARSER = $(addprefix $(PARSER_OBJS_DIR), $(addsuffix .o, $(FILENAMES_PARSER)))

SRCS_MS = $(addprefix $(MS_SRCS_DIR), $(addsuffix .c, $(FILENAMES_MS)))
OBJS_MS = $(addprefix $(MS_OBJS_DIR), $(addsuffix .o, $(FILENAMES_MS)))

SRCS_INIT = $(addprefix $(INIT_SRCS_DIR), $(addsuffix .c, $(FILENAMES_INIT)))
OBJS_INIT = $(addprefix $(INIT_OBJS_DIR), $(addsuffix .o, $(FILENAMES_INIT)))

SRCS_BUILTINS = $(addprefix $(BUILTINS_SRCS_DIR), $(addsuffix .c, $(FILENAMES_BUILTINS)))
OBJS_BUILTINS = $(addprefix $(BUILTINS_OBJS_DIR), $(addsuffix .o, $(FILENAMES_BUILTINS)))

SRCS = $(SRCS_LEXER) ${SRCS_MS} ${SRCS_INIT} ${SRCS_BUILTINS} ${SRCS_PARSER}
OBJS = $(OBJS_LEXER) ${OBJS_MS} ${OBJS_INIT} ${OBJS_BUILTINS} ${OBJS_PARSER}
INCLUDES_DIR = -I./includes/

${NAME}: ${OBJS}
	cc -o ${NAME} $^ -lreadline -L. ./libft/libft.a

.c.o: ${SRCS}
	cc -c -o $@ $< ${INCLUDES_DIR}
	
all: ${NAME}

lib:
	make -C ./libft

clean:
	$(REMOVE) $(OBJS)
	$(REMOVE) $(NAME)

fclean: clean
	rm -rf ${NAME}

re: fclean all

libclean: 
	make fclean -C ./libft




