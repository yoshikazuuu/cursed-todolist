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

bool inMenu;
pthread_t clock_tid;
pthread_mutex_t mutex;
char inTitle[100];

WINDOW *win_todolist;
WINDOW *win_appointment;
WINDOW *win_calendar;
WINDOW *win_clock;
WINDOW *win_menu;

void *clock_thread(void *arg);
void print_centered(WINDOW *win, int start_row, char str[]);
void draw_window_main();
void draw_window_menu(char title[]);
void handle_winch(int sig);
void handle_int(int sig);
void end_screen();
int len_col(WINDOW *win, char str[]);