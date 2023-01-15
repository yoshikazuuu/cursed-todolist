#include "header.h"

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
  // ui_todo();
  print_centered(win_appointment, 0, "APPOINTMENT");
  // ui_appointment();
  print_centered(win_calendar, 0, "CALENDAR");
  // ui_calendar();
  print_centered(win_clock, 0, "CLOCK");

  wrefresh(win_todolist);
  wrefresh(win_appointment);
  wrefresh(win_calendar);
  wrefresh(win_clock);

  // int ret = pthread_kill(clock_tid, 0);
  // if (ret == ESRCH) {
  //   pthread_create(&clock_tid, NULL, clock_thread, win_clock);
  // } else {
  //   pthread_cancel(clock_tid);
  //   pthread_join(clock_tid, NULL);
  // }
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
