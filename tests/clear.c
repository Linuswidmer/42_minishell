#include <curses.h>
#include <stdio.h>
#include <term.h>

void clear_terminal() {
  char* clear_seq = tgetstr("clear", NULL);
  tputs(clear_seq, 1, putchar);
}

int main()
{
	printf("hello world\n");
	clear_terminal();
}
