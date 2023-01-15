#include "header.h"

void print_centered(WINDOW *win, int start_row, char str[]) {
  int center_col = getmaxx(win) / 2;
  int center_str = strlen(str) / 2;
  int adjusted_col = center_col - center_str;

  mvwprintw(win, start_row, adjusted_col, "%s", str);
}

int len_col(WINDOW *win, char str[]) {
  int center_col = getmaxx(win) / 2;
  int center_str = strlen(str) / 2;
  return abs(center_col - center_str);
}

void end_screen() {
  int width, height;
  initscr();
  clear();
  refresh();
  getmaxyx(stdscr, height, width);
  endwin();
  system("clear");
  printf("\e[?25l");
  setvbuf(stdout, NULL, _IOLBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  char *ayaya[] = {
      "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣬⡛⣿⣿⣿⣯⢻\n", "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢻⣿⣿⢟⣻⣿⣿⣿⣿⣿⣿⣮⡻⣿⣿⣧\n",
      "⣿⣿⣿⣿⣿⢻⣿⣿⣿⣿⣿⣿⣆⠻⡫⣢⠿⣿⣿⣿⣿⣿⣿⣿⣷⣜⢻⣿\n", "⣿⣿⡏⣿⣿⣨⣝⠿⣿⣿⣿⣿⣿⢕⠸⣛⣩⣥⣄⣩⢝⣛⡿⠿⣿⣿⣆⢝\n",
      "⣿⣿⢡⣸⣿⣏⣿⣿⣶⣯⣙⠫⢺⣿⣷⡈⣿⣿⣿⣿⡿⠿⢿⣟⣒⣋⣙⠊\n", "⣿⡏⡿⣛⣍⢿⣮⣿⣿⣿⣿⣿⣿⣿⣶⣶⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
      "⣿⢱⣾⣿⣿⣿⣝⡮⡻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⣋⣻⣿⣿⣿⣿\n", "⢿⢸⣿⣿⣿⣿⣿⣿⣷⣽⣿⣿⣿⣿⣿⣿⣿⡕⣡⣴⣶⣿⣿⣿⡟⣿⣿⣿\n",
      "⣦⡸⣿⣿⣿⣿⣿⣿⡛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⣿⣿⣿\n", "⢛⠷⡹⣿⠋⣉⣠⣤⣶⣶⣿⣿⣿⣿⣿⣿⡿⠿⢿⣿⣿⣿⣿⣿⣷⢹⣿⣿\n",
      "⣷⡝⣿⡞⣿⣿⣿⣿⣿⣿⣿⣿⡟⠋⠁⣠⣤⣤⣦⣽⣿⣿⣿⡿⠋⠘⣿⣿\n", "⣿⣿⡹⣿⡼⣿⣿⣿⣿⣿⣿⣿⣧⡰⣿⣿⣿⣿⣿⣹⡿⠟⠉⡀⠄⠄⢿⣿\n",
      "⣿⣿⣿⣽⣿⣼⣛⠿⠿⣿⣿⣿⣿⣿⣯⣿⠿⢟⣻⡽⢚⣤⡞⠄⠄⠄⢸⣿\n"};

  printf("\033[%d;%ldH%s", (height / 2 - 14),
         (width - strlen("ありがとうございます！\n") + 14) / 2,
         "ありがとうございます！\n");

  for (int i = 12; 0 <= i; i--)
    printf("\033[%d;%dH%s", (height / 2 - i), (width - 27) / 2, ayaya[12 - i]);

  printf("\033[%d;%ldH%s", (height / 2 + 2),
         (width - strlen("⭐ AYAYA! ⭐\n") + 4) / 2, "⭐ AYAYA! ⭐\n");

  printf("\033[%d;%ldH%s", (height / 2 + 4),
         (width - strlen("press enter to continue\n") + 2) / 2,
         "press enter to continue\n");

  getch();
  system("clear");
  printf("\e[?25h");
  system("pause");
  system("stty sane");
}