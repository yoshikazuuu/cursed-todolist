#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *month_name[12] = {"January",   "February", "March",    "April",
                              "May",       "June",     "July",     "August",
                              "September", "October",  "November", "December"};
const char *day_names = "Su Mo Tu We Th Fr Sa";
int num_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

#define WHTB "\033[30m\033[47m"
#define RST "\033[0m"

int *get_current_date() {
  static int date[3];
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  date[0] = tm.tm_mday;
  date[1] = tm.tm_mon;
  date[2] = tm.tm_year + 1900;
  return date;
}

is_leap_year(int y) { return ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0); }

int month_start_day(int y, int m) {
  int total_days = 1;

  total_days += (y - 1) * 365;
  int leaps = ((y - 1) / 4) + ((y - 1) / 400) - ((y - 1) / 100);
  total_days += leaps;

  for (int i = 0; i < m; i++) {
    total_days += num_days[i];
  }

  return total_days % 7;
}

int month_start_week(int y, int m) {
  int total_days = month_start_day(y, 0);
  int week = 1;
  for (int i = 0; i < m; i++) {
    total_days += num_days[i];
  }

  week += total_days / 7;
  return week;
}

int year_char_len(int y) {
  int count = 0;
  while (y != 0) {
    y /= 10;
    count++;
  }

  return count;
}

void print_spaces(int n) {
  for (int i = 0; i < n; i++) {
    printf(" ");
  }
}

void print_heading(int y, int m, int n, int w, int s) {
  int include_year = 0;
  if (s == 1) {
    include_year = year_char_len(y) + 1;
  }

  for (int i = 0; i < n; i++) {
    int month_name_len = strlen(month_name[m + i]);
    int num_spaces = (20 - (month_name_len + include_year)) / 2;
    int remainder = (20 - (month_name_len + include_year)) % 2;

    print_spaces(num_spaces + (w * 3));
    printf("%s", month_name[m + i]);
    if (s == 1) {
      printf(" %d", y);
    }
    print_spaces(num_spaces + remainder + 2 + w);
  }

  printf("\n");

  for (int j = 0; j < n; j++) {
    if (w)
      print_spaces(3);
    printf("%s", day_names);
    print_spaces(2 + w);
  }

  printf("\n");
}

void print_day_numbers(int y, int m, int n, int w) {

  int remaining_days = 0;
  int start_day[n];
  int days_printed[n];
  int week[n];
  int *date = get_current_date();

  for (int i = 0; i < n; i++) {
    remaining_days += num_days[m + i];
    start_day[i] = month_start_day(y, m + i);
    days_printed[i] = 1;
    if (w)
      week[i] = month_start_week(y, m + i);
  }

  n--;

  int month_pointer = 0;
  int day_pointer = 0;

  while (remaining_days > 0) {
    if (w) {
      if (day_pointer == 0 &&
          days_printed[month_pointer] <= num_days[month_pointer + m]) {
        if (week[month_pointer] < 10) {
          print_spaces(1);
        }
        printf("%d ", week[month_pointer]);
        week[month_pointer]++;
      } else if (day_pointer == 0) {
        print_spaces(3);
      }
    }

    if (start_day[month_pointer] > 0) {
      print_spaces(start_day[month_pointer] * 3);
      day_pointer = start_day[month_pointer];
      start_day[month_pointer] = -1;
    } else if (days_printed[month_pointer] > num_days[month_pointer + m]) {
      print_spaces((7 - day_pointer) * 3);
      day_pointer = 7;
    } else {
      if (y == date[2] && m + month_pointer == date[1] &&
          days_printed[month_pointer] == date[0]) {
        printf(WHTB);
        if (days_printed[month_pointer] < 10) {
          print_spaces(1);
        }
        printf("%d", days_printed[month_pointer]);
        printf(RST);
        print_spaces(1);
        days_printed[month_pointer]++;
        day_pointer++;
        remaining_days--;
      } else {
        if (days_printed[month_pointer] < 10) {
          print_spaces(1);
        }
        printf("%d ", days_printed[month_pointer]);
        days_printed[month_pointer]++;
        day_pointer++;
        remaining_days--;
      }
    }
    if (day_pointer % 7 == 0 && month_pointer != n) {
      print_spaces(1 + w);
      month_pointer++;
      day_pointer = 0;
    } else if (day_pointer % 7 == 0 && month_pointer == n) {
      printf("\n");
      month_pointer = 0;
      day_pointer = 0;
    }
  }
  printf("\n");
}

void print_calendar(int y, int m, int n, int w, int s) {
  num_days[1] = (is_leap_year(y)) ? 29 : 28;
  print_heading(y, m, n, w, s);
  print_day_numbers(y, m, n, w);
}

void print_help() {
  printf("How to use:\n[compiled program] [options]\n\nRunning program without "
         "arguments will print current month\n\nOptions:\n -y <num>\tYear to "
         "print\n\t\t  Note: Prints whole year if -m is not specified\n -m "
         "<num>\tMonth to print\n\t\t  Note: January = 0\n -w\t\tPrint week "
         "numbers\n -n <num>\tNumber of months to print\n\t\t  Note: Will only "
         "print until end of year\n\t\t\tStarts from current month if -m is "
         "not specified\n\t\t\tPrints whole year if used with -y without -m\n "
         "-h\t\tDisplay this help page\n");
}

void print_year(int y, int w) {
  int heading_len = (w) ? 78 : 64;
  int year_len = year_char_len(y);
  int num_spaces = (heading_len - year_len) / 2;
  printf("\n");
  print_spaces(num_spaces);
  printf("%d", y);
  printf("\n\n");
  for (int i = 0; i < 4; i++) {
    print_calendar(y, i * 3, 3, w, 0);
    printf("\n");
  }
}

int init(int y, int m, int n, int w) {
  int *date = get_current_date();
  int s = 0;
  if (y > 0 && m < 0) {
    print_year(y, w);
    return 0;
  }
  if (y < 1) {
    y = date[2];
  }
  if (m < 0) {
    m = date[1];
  }
  if (n == 12) {
    print_year(y, w);
    return 0;
  } else if (m + n > 12) {
    n = 12 - m;
  } else if (n < 1) {
    n = 1;
  }
  if (n > 3) {
    while (n > 3) {
      printf("\n");
      print_calendar(y, m, 3, w, 0);
      m += 3;
      n -= 3;
    }
    printf("\n");
    print_calendar(y, m, n, w, 0);
    return 0;
  }
  if (n == 1) {
    s = 1;
  }
  print_calendar(y, m, n, w, s);
  return 0;
}

int main(int argc, char *argv[]) {
  int y = 0, m = -1, n = 0, w = 0;

  for (int i = 1; i < argc; i++) {
    char c = argv[i][1];
    switch (c) {
    case 'w':
      w = 1;
      break;
    case 'n':
      if (argv[i + 1]) {
        n = atoi(argv[i + 1]);
        i += 1;
        break;
      } else {
        print_help();
        return 0;
      }
    case 'm':
      if (argv[i + 1]) {
        m = atoi(argv[i + 1]);
        i += 1;
        break;
      } else {
        print_help();
        return 0;
      }
    case 'y':
      if (argv[i + 1]) {
        y = atoi(argv[i + 1]);
        i += 1;
        break;
      } else {
        print_help();
        return 0;
      }
    default:
      print_help();
      return 0;
    }
  }

  init(y, m, n, w);

  return 0;
}