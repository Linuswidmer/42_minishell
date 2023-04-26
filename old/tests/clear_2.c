#include <sys/ioctl.h>
#include <stdio.h>

void clear_terminal() {
  struct winsize w;
  ioctl(1, TIOCGWINSZ, &w);
  for (int i = 0; i < w.ws_row; i++) {
    putchar('\n');
  }
}

int main()
{
	clear_terminal();
}
