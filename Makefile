# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 09:41:35 by lwidmer           #+#    #+#              #
#    Updated: 2023/06/02 12:25:06 by lwidmer          ###   ########.fr        #
#    Updated: 2023/05/07 23:38:37 by lwidmer          ###   ########.fr        #
#    Updated: 2023/05/02 17:30:33 by lwidmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

define MAKE_SRCS
	SRCS_$(1) = $(addprefix $(2), $(addsuffix .c, $(FILENAMES_$(1))))
endef

define MAKE_OBJS
	OBJS_$(1) = $(addprefix $(2), $(addsuffix .o, $(FILENAMES_$(1))))
endef

define MAKE_SRCS_OBJS
    $(eval SRCS_$(1) := $(addprefix $(2), $(addsuffix .c, $$(FILENAMES_$(1)))))
    $(eval OBJS_$(1) := $(addprefix $(2), $(addsuffix .o, $$(FILENAMES_$(1)))))
endef

NAME = minishell

DIRS := \
    LEXER \
    PARSER \
    MS \
    INIT \
    BUILTINS \
    JOB \
    EXPANDER \
    EXECUTER \
    PIPE \
    FREE \
    ERROR

SRCS_DIRS := \
    ./src_lexer/ \
    ./parser/ \
    ./src/ \
    ./init/ \
    ./builtins/ \
    ./job/ \
    ./expander/ \
    ./executer/ \
    ./pipe/ \
    ./free/ \
    ./error/

DIR_PATHS = \
	./src_lexer/ \
	./parser/ \
	./src/ \
	./init/ \
	./builtins/ \
	./job/ \
	./expander/ \
	./executer/ \
	./pipe/ \
	./free/ \
	./error \

FILENAMES_LEXER = lexer tokens token_parser lexer_utils free_lexer token_list_utils \
				dollar_postprocessing parse_quote parse_dollar

FILENAMES_PARSER = min_token_is_para min_jobnode	min_parser_malloc_fail  min_token_is_route min_pipenode min_subnode min_token_is_word  min_routenode min_token_is_io min_parser  min_token_is_io_in min_debug min_heredoc_fail min_free_ast min_heredoc min_add_io_to_sub min_bring_ast_to_beginning min_is_last_token min_token_is_jobnode

FILENAMES_MS = main

FILENAMES_INIT = signals init dict min_dict_utils min_shlvl free_dict_builtins_min builtins 

FILENAMES_BUILTINS = cd echo env exit export export_utils pwd unset min_builtins_wrapper_1 min_builtins_wrapper_2

FILENAMES_JOB = min_buildin_cmd min_ex_get_cmd min_expander min_set_cmd min_common_cmd min_ex_io min_io_and_cmd min_set_io min_get_envp

FILENAMES_EXPANDER =  min_free_expander min_last_expander min_word_eval min_init_expander min_word min_til min_dollar min_asterisk min_evaluate_asterisk min_add_extra_to_word min_init_exphelp min_addlast_expander min_get_all_asterisk_members min_add_value_to_expander min_asterisk_splitvalue min_check_dict min_check_word min_delimter_split min_eval_dollar min_eval_splitvalue min_len_split min_to_aste

FILENAMES_EXECUTER = min_executer min_exit_handler min_job min_sub min_route

FILENAMES_PIPE = min_pipe min_pipe_loop pipe_redirection
	
FILENAMES_FREE = min_free

FILENAMES_ERROR = min_parser_error

$(eval $(call MAKE_SRCS,LEXER,./src_lexer/))
$(eval $(call MAKE_OBJS,LEXER,./src_lexer/))

$(eval $(call MAKE_SRCS,PARSER,./parser/))
$(eval $(call MAKE_OBJS,PARSER,./parser/))

$(eval $(call MAKE_SRCS,MS,./src/))
$(eval $(call MAKE_OBJS,MS,./src/))

$(eval $(call MAKE_SRCS,INIT,./init/))
$(eval $(call MAKE_OBJS,INIT,./init/))

$(eval $(call MAKE_SRCS,BUILTINS,./builtins/))
$(eval $(call MAKE_OBJS,BUILTINS,./builtins/))

$(eval $(call MAKE_SRCS,JOB,./job/))
$(eval $(call MAKE_OBJS,JOB,./job/))

$(eval $(call MAKE_SRCS,EXPANDER,./expander/))
$(eval $(call MAKE_OBJS,EXPANDER,./expander/))

$(eval $(call MAKE_SRCS,EXECUTER,./executer/))
$(eval $(call MAKE_OBJS,EXECUTER,./executer/))

$(eval $(call MAKE_SRCS,PIPE,./pipe/))
$(eval $(call MAKE_OBJS,PIPE,./pipe/))

$(eval $(call MAKE_SRCS,FREE,./free/))
$(eval $(call MAKE_OBJS,FREE,./free/))

$(eval $(call MAKE_SRCS,ERROR,./error/))
$(eval $(call MAKE_OBJS,ERROR,./error/))

SRCS = $(SRCS_LEXER) ${SRCS_MS} ${SRCS_INIT} ${SRCS_BUILTINS} ${SRCS_PARSER} ${SRCS_JOB} ${SRCS_EXPANDER} ${SRCS_EXECUTER} ${SRCS_PIPE} ${SRCS_FREE} ${SRCS_ERROR}
OBJS = $(OBJS_LEXER) ${OBJS_MS} ${OBJS_INIT} ${OBJS_BUILTINS} ${OBJS_PARSER} ${OBJS_JOB} ${OBJS_EXPANDER} ${OBJS_EXECUTER} ${OBJS_PIPE} ${OBJS_FREE} ${OBJS_ERROR}

INCLUDES_DIR = -I./includes/

REMOVE = rm -f

CFLAGS = -Werror -Wall -Wextra

${NAME}: ${OBJS}
	cc -o ${NAME} $^ -lreadline -L. ./libft/libft.a

.c.o: ${SRCS}
	cc -c -o $@ $< ${INCLUDES_DIR}
	
all: ${NAME}

lib:
	make -C ./libft

clean:
	$(REMOVE) $(OBJS)

fclean: clean
	rm -rf ${NAME}

re: fclean all

libclean: 
	make fclean -C ./libft


