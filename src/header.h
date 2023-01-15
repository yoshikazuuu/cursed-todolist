#include <curses.h>
#include <errno.h>
#include <locale.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// COLOR
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

// GLOBAL
bool inMenu;
pthread_t clock_tid;
pthread_mutex_t mutex;
char inTitle[100];
char *months[] = {"January",   "February", "March",    "April",
                  "May",       "June",     "July",     "August",
                  "September", "October",  "November", "December"};

// WINDOWS
WINDOW *win_todolist;
WINDOW *win_appointment;
WINDOW *win_calendar;
WINDOW *win_clock;
WINDOW *win_menu;

// MAIN SCREEN related
void *clock_thread(void *arg);
void print_centered(WINDOW *win, int start_row, char str[]);
void draw_window_main();
void draw_window_menu(char title[]);
void handle_winch(int sig);
void handle_int(int sig);
void input_timeout(int sig);
void end_screen();
int len_col(WINDOW *win, char str[]);
void remove_enter(char str[]);

// TO DO LIST related
void add_todo();
void remove_todo(int line);
void ui_todo();
void ui_calendar();
void ui_appointment();
// void ui_calendar();

// STRUCTS
struct list {
  char list[100];
};