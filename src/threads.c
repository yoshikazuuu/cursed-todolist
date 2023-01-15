#include "header.h"

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

    strncat(date_string, " ", sizeof(date_string) - strlen(date_string) - 1);
    strncat(date_string, suffix, sizeof(date_string) - strlen(date_string) - 1);

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
