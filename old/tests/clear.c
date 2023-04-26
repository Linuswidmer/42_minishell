#include <curses.h>
#include <stdio.h>
#include <term.h>
#include "t.h"

/*void clear_terminal() {
  char* clear_seq = tgetstr("clear", NULL);
  tputs(clear_seq, 1, putchar);
}*/

//int i = 0;

int add(int a);

int main()
{
 i = 0;
	
	i = add(5);
	i = add(10);
	printf("%i", i);
	return (0);
}

int add(int a)
{
return (a + i);
}

