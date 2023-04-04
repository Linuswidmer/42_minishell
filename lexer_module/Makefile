# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 16:53:37 by lwidmer           #+#    #+#              #
#    Updated: 2023/04/04 13:26:34 by lwidmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lexer

FILENAMES = lexer_main utils tokens check_token_list

SRCS_DIR = ./
OBJS_DIR = ./

SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILENAMES)))
OBJS= $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILENAMES)))

${NAME}: ${OBJS}
	cc -o ${NAME} $^

.c.o: ${SRCS}
	cc -c -o $@ $< -I lexer.h

test: ${NAME}
	./lexer "< infile || infile2 echo -n		 'e >>c  ec bla' >> outfile    "

readline:
	cc readline.c -lreadline
