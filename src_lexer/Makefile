# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 16:53:37 by lwidmer           #+#    #+#              #
#    Updated: 2023/04/21 12:50:44 by lwidmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lexer

FILENAMES = main lexer tokens check_token_list lexer_parser expander lexer_utils free_lexer utils get_next_line get_next_line_utils

SRCS_DIR = ./
OBJS_DIR = ./

SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILENAMES)))
OBJS= $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILENAMES)))

INLCUDES_DIR=-I../libft/includes

${NAME}: ${OBJS}
	cc -o ${NAME} $^ -lreadline -L ../libft/libft.a

.c.o: ${SRCS}
	cc -c -o $@ $< ${INCLUDES_DIR}

simple_test: ${NAME}
	./lexer "echo    hello world  "

test: ${NAME}
	./lexer "< infile || infile2 'echo' -n	| 'e >>c  ec bla' >> outfile    "

quotes: ${NAME}
	./lexer "echo ''    ' < hello''' "

no_spaces: ${NAME}
	./lexer "echo <infile'helloworld'>outfile"

empty_quotes: ${NAME}
	./lexer "echo ''hello"

simple_quotes: ${NAME}
	./lexer "echo 'hello world'test'hello'"

dollar: ${NAME}
	./lexer 

memory: ${NAME}
	valgrind --leak-check=full ./lexer "bla vla 'hello' << || &&     "

readline:
	cc readline.c -lreadline
