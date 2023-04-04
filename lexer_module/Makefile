# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 16:53:37 by lwidmer           #+#    #+#              #
#    Updated: 2023/04/03 16:58:58 by lwidmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

lex:
	cc lexer_main.c && ./a.out "< infile | infile2 echo -n  'e >>c  ec bla' > outfile    "

readline:
	cc readline.c -lreadline

lexer:
	cc lexer_main.c && ./a.out "< infile echo 'hello world' > outfile"
