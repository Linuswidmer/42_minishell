# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 09:41:35 by lwidmer           #+#    #+#              #
#    Updated: 2023/05/09 08:47:57 by jstrotbe         ###   ########.fr        #
#    Updated: 2023/05/02 17:30:33 by lwidmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


define MAKE_SRCS
	SRCS_$(1) = $(addprefix $(2), $(addsuffix .c, $(FILENAMES_$(1))))
endef

define MAKE_OBJS
	OBJS_$(1) = $(addprefix $(2), $(addsuffix .o, $(FILENAMES_$(1))))
endef

NAME = minishell

REMOVE = rm -f

FILENAMES_LEXER = lexer tokens check_token_list lexer_parser lexer_utils free_lexer token_list_utils \
				dollar_postprocessing

FILENAMES_PARSER = min_token_is_para min_jobnode	min_parser_malloc_fail  min_token_is_route min_pipenode min_subnode min_token_is_word  min_routenode min_token_is_io min_parser  min_token_is_io_in min_debug min_heredoc_fail min_free_ast min_heredoc min_add_io_to_sub min_bring_ast_to_beginning min_is_last_token

FILENAMES_MS = main

FILENAMES_INIT = signals init dict free_dict_builtins_min builtins builtins_wrapper

FILENAMES_BUILTINS = cd echo env exit export pwd unset

FILENAMES_JOB = min_buildin_cmd min_ex_get_cmd min_expander min_set_cmd min_common_cmd min_ex_io min_io_and_cmd min_set_io min_get_envp

FILENAMES_EXPANDER = min_asterisk min_free_expander min_last_expander min_word_eval min_dollar min_init_expander min_word min_til

FILENAMES_EXECUTER = min_executer min_exit_handler min_job min_sub min_route

FILENAMES_PIPE = min_pipe
	
FILENAMES_FREE = min_free

FILENAMES_ERROR = min_parser_error


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

JOB_SRCS_DIR = ./job/
JOB_OBJS_DIR = ./job/

EXPANDER_SRCS_DIR = ./expander/
EXPANDER_OBJS_DIR = ./expander/

EXECUTER_SRCS_DIR = ./executer/
EXECUTER_OBJS_DIR = ./executer/

PIPE_SRCS_DIR = ./pipe/
PIPE_OBJS_DIR = ./pipe/

FREE_SRCS_DIR = ./free/
FREE_OBJS_DIR = ./free/

ERROR_SRCS_DIR = ./error/
ERROR_OBJS_DIR = ./error/


#SRCS_LEXER = $(addprefix $(LEXER_SRCS_DIR), $(addsuffix .c, $(FILENAMES_LEXER)))
$(MAKE_SRCS, LEXER, ./src_lexer/)
SRCS_LEXER = $(addprefix $(LEXER_SRCS_DIR), $(addsuffix .c, $(FILENAMES_LEXER)))
OBJS_LEXER = $(addprefix $(LEXER_OBJS_DIR), $(addsuffix .o, $(FILENAMES_LEXER)))
#$(MAKE_OBJS, LEXER, ./src_lexer/)

SRCS_PARSER = $(addprefix $(PARSER_SRCS_DIR), $(addsuffix .c, $(FILENAMES_PARSER)))
OBJS_PARSER = $(addprefix $(PARSER_OBJS_DIR), $(addsuffix .o, $(FILENAMES_PARSER)))

SRCS_MS = $(addprefix $(MS_SRCS_DIR), $(addsuffix .c, $(FILENAMES_MS)))
OBJS_MS = $(addprefix $(MS_OBJS_DIR), $(addsuffix .o, $(FILENAMES_MS)))

SRCS_INIT = $(addprefix $(INIT_SRCS_DIR), $(addsuffix .c, $(FILENAMES_INIT)))
OBJS_INIT = $(addprefix $(INIT_OBJS_DIR), $(addsuffix .o, $(FILENAMES_INIT)))

SRCS_BUILTINS = $(addprefix $(BUILTINS_SRCS_DIR), $(addsuffix .c, $(FILENAMES_BUILTINS)))

OBJS_BUILTINS = $(addprefix $(BUILTINS_OBJS_DIR), $(addsuffix .o, $(FILENAMES_BUILTINS)))

SRCS_JOB = $(addprefix $(JOB_SRCS_DIR), $(addsuffix .c, $(FILENAMES_JOB)))
OBJS_JOB = $(addprefix $(JOB_OBJS_DIR), $(addsuffix .o, $(FILENAMES_JOB)))

SRCS_EXPANDER = $(addprefix $(EXPANDER_SRCS_DIR), $(addsuffix .c, $(FILENAMES_EXPANDER)))
OBJS_EXPANDER = $(addprefix $(EXPANDER_OBJS_DIR), $(addsuffix .o, $(FILENAMES_EXPANDER)))

SRCS_EXECUTER = $(addprefix $(EXECUTER_SRCS_DIR), $(addsuffix .c, $(FILENAMES_EXECUTER)))
OBJS_EXECUTER = $(addprefix $(EXECUTER_OBJS_DIR), $(addsuffix .o, $(FILENAMES_EXECUTER)))

OBJS_PIPE = $(addprefix $(PIPE_OBJS_DIR), $(addsuffix .o, $(FILENAMES_PIPE)))
SRCS_PIPE = $(addprefix $(PIPE_SRC_DIR), $(addsuffix .c, $(FILENAMES_PIPE)))

OBJS_FREE = $(addprefix $(FREE_OBJS_DIR), $(addsuffix .o, $(FILENAMES_FREE)))
SRCS_FREE = $(addprefix $(FREE_SRC_DIR), $(addsuffix .c, $(FILENAMES_FREE)))

OBJS_ERROR = $(addprefix $(ERROR_OBJS_DIR), $(addsuffix .o, $(FILENAMES_ERROR)))
SRCS_ERROR = $(addprefix $(ERROR_SRC_DIR), $(addsuffix .c, $(FILENAMES_ERROR)))


SRCS = $(SRCS_LEXER) ${SRCS_MS} ${SRCS_INIT} ${SRCS_BUILTINS} ${SRCS_PARSER} ${SRCS_JOB} ${SRCS_EXPANDER} ${SRCS_EXECUTER} ${SRCS_PIPE} ${SRCS_FREE} ${SRCS_ERROR}
OBJS = $(OBJS_LEXER) ${OBJS_MS} ${OBJS_INIT} ${OBJS_BUILTINS} ${OBJS_PARSER} ${OBJS_JOB} ${OBJS_EXPANDER} ${OBJS_EXECUTER} ${OBJS_PIPE} ${OBJS_FREE} ${OBJS_ERROR}
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




