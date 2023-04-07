#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

void clear_terminal() {
  // Save cursor position
  printf("\033[s");

  // Clear screen
  printf("\033[2J");

  // Move cursor to top left corner
  printf("\033[H");

  // Restore cursor position
  //printf("\033[u");
}

int main() {
  printf("Hello, world!\n");
  clear_terminal();
  return 0;
}
