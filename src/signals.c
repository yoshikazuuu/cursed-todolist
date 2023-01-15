#include "header.h"

void handle_winch(int sig) {
  endwin();
  refresh();
  clear();

  resizeterm(LINES, COLS);

  (inMenu) ? draw_window_menu(inTitle) : draw_window_main();
  doupdate();
}

void handle_int(int sig) {
  endwin();

  exit(1);
}
