FILENAMES = main signals dict ./builtins/export ./builtins/cd ./builtins/pwd ./builtins/env \
			./builtins/unset ./builtins/echo ./builtins/exit builtins_wrapper builtins
SRCS = $(addsuffix .c, $(FILENAMES))
OBJS = $(addsuffix .o, $(FILENAMES))


init: ${OBJS}
	cc  $^ -L. ../libft/libft.a -lreadline

.c.o: ${SRCS}
	cc -c -o $@ $< -I../libft/includes
