FILENAMES = dict builtins builtins_wrappers export cd unset env
SRCS = $(addsuffix .c, $(FILENAMES))
OBJS = $(addsuffix .o, $(FILENAMES))


test: ${OBJS}
	cc  $^ -L. ../libft/libft.a

.c.o: ${SRCS}
	cc -c -o $@ $< -I../libft/includes
