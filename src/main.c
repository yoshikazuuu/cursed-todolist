#include "header.h"

int main() {
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  signal(SIGWINCH, handle_winch);
  signal(SIGINT, handle_int);

  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
  } else {
    start_color();
    use_default_colors();
    draw_window_main();
    inMenu = false;
    // pthread_mutex_init(&mutex, NULL);
  }

  char ch = '\0';
  while (ch != 'q') {
    // setlocale(LC_ALL, "");
    setlocale(LC_ALL, "en_US.UTF-8");

    ch = getch();
    switch (ch) {
    case 'a':
      inMenu = true;
      strcpy(inTitle, "APPOINTMENT");
      draw_window_menu(inTitle);
      wgetch(win_menu);
      break;
    case 't':
      inMenu = true;
      strcpy(inTitle, "TO DO LIST");
      draw_window_menu(inTitle);
      wgetch(win_menu);
      break;
    case 'c':
      inMenu = true;
      strcpy(inTitle, "CALENDAR");
      draw_window_menu(inTitle);
      wgetch(win_menu);
      break;
    default:
      draw_window_main();
      inMenu = false;
      break;
    }
    draw_window_main();
    inMenu = false;
  }

  end_screen();

  // pthread_mutex_destroy(&mutex);
  return 0;
}