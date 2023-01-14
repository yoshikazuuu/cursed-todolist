#include <errno.h>
#include <locale.h>
#include <ncurses.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

char *ayaya[] = {"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣬⡛⣿⣿⣿⣯⢻", "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢻⣿⣿⢟⣻⣿⣿⣿⣿⣿⣿⣮⡻⣿⣿⣧",
                 "⣿⣿⣿⣿⣿⢻⣿⣿⣿⣿⣿⣿⣆⠻⡫⣢⠿⣿⣿⣿⣿⣿⣿⣿⣷⣜⢻⣿", "⣿⣿⡏⣿⣿⣨⣝⠿⣿⣿⣿⣿⣿⢕⠸⣛⣩⣥⣄⣩⢝⣛⡿⠿⣿⣿⣆⢝",
                 "⣿⣿⢡⣸⣿⣏⣿⣿⣶⣯⣙⠫⢺⣿⣷⡈⣿⣿⣿⣿⡿⠿⢿⣟⣒⣋⣙⠊", "⣿⡏⡿⣛⣍⢿⣮⣿⣿⣿⣿⣿⣿⣿⣶⣶⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿",
                 "⣿⢱⣾⣿⣿⣿⣝⡮⡻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⣋⣻⣿⣿⣿⣿", "⢿⢸⣿⣿⣿⣿⣿⣿⣷⣽⣿⣿⣿⣿⣿⣿⣿⡕⣡⣴⣶⣿⣿⣿⡟⣿⣿⣿",
                 "⣦⡸⣿⣿⣿⣿⣿⣿⡛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⣿⣿⣿", "⢛⠷⡹⣿⠋⣉⣠⣤⣶⣶⣿⣿⣿⣿⣿⣿⡿⠿⢿⣿⣿⣿⣿⣿⣷⢹⣿⣿",
                 "⣷⡝⣿⡞⣿⣿⣿⣿⣿⣿⣿⣿⡟⠋⠁⣠⣤⣤⣦⣽⣿⣿⣿⡿⠋⠘⣿⣿", "⣿⣿⡹⣿⡼⣿⣿⣿⣿⣿⣿⣿⣧⡰⣿⣿⣿⣿⣿⣹⡿⠟⠉⡀⠄⠄⢿⣿",
                 "⣿⣿⣿⣽⣿⣼⣛⠿⠿⣿⣿⣿⣿⣿⣯⣿⠿⢟⣻⡽⢚⣤⡞⠄⠄⠄⢸⣿"};

char *anime[] = {
    "⠄⠄⠄⠄⠄⠄⠄⠄⢀⣠⣤⣤⣤⣤⣤⣤⣤⣤⣀⣀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄", "⠄⠄⠄⠄⠄⣠⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣄⠄⠄⠄⠄⠄⠄⠄",
    "⠄⠄⠄⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⠿⠿⢿⣿⣿⣷⣄⠄⠄⠄⠄⠄", "⠄⠄⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⣠⣶⣶⣶⣶⣤⡉⠻⣿⣿⣷⣀⠄⠄⠄",
    "⠄⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣼⣿⣿⣿⣿⣿⣿⣿⣶⣿⣿⣿⣿⡆⠄⠄", "⠄⣿⡿⠟⠛⠛⠛⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀⠄",
    "⠄⠁⣴⣾⣿⣿⣿⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⢿⣿⡿⠛⠉⠉⣿⣿⣿⣧⠄", "⠄⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣏⣠⡼⠛⣁⣴⣶⣶⣿⣿⣿⡿⠄",
    "⠄⠸⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣤⣾⣿⣿⣿⣿⣿⣿⣿⡇⠄", "⠄⠄⠹⣿⣿⠟⠛⠛⠁⣀⣉⣿⣿⣿⣿⣿⣿⠿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠄",
    "⠄⠄⠄⠙⢫⣶⣶⣿⣿⣿⣿⣿⣿⠿⠋⣁⣤⣴⣶⣶⣦⡙⢿⣿⣿⣿⣿⠏⠄⠄", "⠄⠄⠄⠄⠄⢻⣿⣿⣿⣿⣿⣿⣯⠄⣾⣿⣿⣿⣿⡿⠿⠃⢸⣿⡿⠋⠄⠄⠄⠄",
    "⠄⠄⠄⠄⠄⠘⢿⣿⣿⣿⣿⣿⣿⣦⡙⠛⣉⣡⣤⡴⠖⠄⠚⠋⠄⠄⠄⠄⠄⠄", "⠄⠄⠄⠄⠄⠄⠄⠙⠛⠛⠛⠛⠛⠛⠛⠒⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄",
};

volatile bool inMenu = false;
pthread_t clock_tid;
pthread_mutex_t mutex;
char inTitle[100];

WINDOW *win_todolist;
WINDOW *win_appointment;
WINDOW *win_calendar;
WINDOW *win_clock;
WINDOW *win_menu;

void *clock_thread(void *arg);

void print_centered(WINDOW *win, int start_row, char str[]) {
  int center_col = getmaxx(win) / 2;
  int center_str = strlen(str) / 2;
  int adjusted_col = center_col - center_str;

  mvwprintw(win, start_row, adjusted_col, "%s", str);
}

void draw_window_main() {
  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);

  if (xMax % 2 != 0) {
    xMax--;
  }
  if (yMax % 2 != 0) {
    yMax--;
  }

  win_todolist = newwin(yMax - 8, xMax / 2, 0, 0);
  win_appointment = newwin(yMax - 7, xMax / 2, 7, xMax / 2);
  win_calendar = newwin(8, xMax / 2, yMax - 8, 0);
  win_clock = newwin(7, xMax / 2, 0, xMax / 2);

  box(win_todolist, 0, 0);
  box(win_appointment, 0, 0);
  box(win_calendar, 0, 0);
  box(win_clock, 0, 0);
  refresh();

  print_centered(win_todolist, 0, "TO DO LIST");
  print_centered(win_appointment, 0, "APPOINTMENT");
  print_centered(win_calendar, 0, "CALENDAR");
  print_centered(win_clock, 0, "CLOCK");

  wrefresh(win_todolist);
  wrefresh(win_appointment);
  wrefresh(win_calendar);
  wrefresh(win_clock);

  int ret = pthread_kill(clock_tid, 0);
  if (ret == ESRCH) {
    pthread_create(&clock_tid, NULL, clock_thread, win_clock);
  } else {
    pthread_cancel(clock_tid);
    pthread_join(clock_tid, NULL);
  }
}

void draw_window_menu(char title[]) {

  clear();
  refresh();
  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);

  double multiplier = 1.3;

  win_menu = newwin(yMax / multiplier, xMax / multiplier,
                    (yMax - (yMax / multiplier)) / 2,
                    (xMax - (xMax / multiplier)) / 2 + 1);
  box(win_menu, 0, 0);
  print_centered(win_menu, 0, title);
  wrefresh(win_menu);
}

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

int len_col(WINDOW *win, char str[]) {
  int center_col = getmaxx(win) / 2;
  int center_str = strlen(str) / 2;
  return center_col - center_str;
}

void *clock_thread(void *arg) {
  pthread_mutex_lock(&mutex);
  while (!inMenu) {
    pthread_mutex_unlock(&mutex);

    WINDOW *win = (WINDOW *)arg;
    start_color();
    use_default_colors();
    init_pair(1, COLOR_YELLOW, -1);
    init_pair(2, COLOR_GREEN, -1);
    time_t current_time = time(NULL);
    struct tm *time_info = localtime(&current_time);

    int day = time_info->tm_mday;
    char suffix[5];

    if (day % 10 == 1 && day != 11) {
      snprintf(suffix, 5, "%dst", day);
    } else if (day % 10 == 2 && day != 12) {
      snprintf(suffix, 5, "%dnd", day);
    } else if (day % 10 == 3 && day != 13) {
      snprintf(suffix, 5, "%drd", day);
    } else {
      snprintf(suffix, 5, "%dth", day);
    }

    char time_string[9];
    char date_string[30];
    strftime(date_string, sizeof(date_string), "%A, %B", time_info);
    strftime(time_string, sizeof(time_string), "%H:%M:%S", time_info);

    sprintf(date_string, "%s %s", date_string, suffix);

    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, 2, len_col(win, date_string), "%s", date_string);
    wattroff(win, COLOR_PAIR(1));
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 4, len_col(win, time_string), "%s", time_string);
    wattroff(win, COLOR_PAIR(2));
    refresh();
    wrefresh(win);
    sleep(1);
  }
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
  return NULL;
}

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
    pthread_mutex_init(&mutex, NULL);
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

  inMenu = true;
  strcpy(inTitle, "THANK YOU");
  draw_window_menu(inTitle);
  int center_col = getmaxx(win_menu) / 2;
  int center_str = strlen(anime[0]) / 2;
  int adjusted_col = center_str - center_col;
  for (int i = 1; i <= 13; i++) {
    mvwprintw(win_menu, i + (getmaxy(win_menu) - 13) / 2, adjusted_col,
              anime[i - 1]);
  }
  print_centered(win_menu, getmaxy(win_menu) - 2, "press any key to continue");
  refresh();
  wrefresh(win_menu);
  wgetch(win_menu);

  pthread_mutex_destroy(&mutex);
  endwin();

  return 0;
}