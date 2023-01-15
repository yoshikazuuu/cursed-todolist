#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define __USE_XOPEN
#include <time.h>
#include <unistd.h>

struct Appointment {
  struct tm startTime;
  struct tm endTime;
  char *description;
};

// create appointments.txt if don't exists
void createAppointmentsFile() {
  FILE *appointments_file = fopen("appointments.txt", "r");
  if (appointments_file == NULL) {
    appointments_file = fopen("appointments.txt", "w");
    fclose(appointments_file);
  } else {
    fclose(appointments_file);
  }
}

void createAppointment(struct Appointment *appointment) {
  FILE *appointments_file = fopen("appointments.txt", "a");
  if (appointments_file == NULL) {
    printf("Error: Could not open appointments file\n");
    return;
  }

  printf("Enter start time (YYYY-MM-DD HH:MM): ");
  scanf("%d-%d-%d %d:%d", &appointment->startTime.tm_year,
        &appointment->startTime.tm_mon, &appointment->startTime.tm_mday,
        &appointment->startTime.tm_hour, &appointment->startTime.tm_min);

  getchar();

  printf("Enter end time (YYYY-MM-DD HH:MM): ");
  scanf("%d-%d-%d %d:%d", &appointment->endTime.tm_year,
        &appointment->endTime.tm_mon, &appointment->endTime.tm_mday,
        &appointment->endTime.tm_hour, &appointment->endTime.tm_min);

  getchar();

  char *description = malloc(100);
  printf("Enter description: ");
  scanf("%[^\n]s", description);
  appointment->description = description;

  fprintf(appointments_file, "%d-%d-%d %d:%d~%d-%d-%d %d:%d~%s\n",
          appointment->startTime.tm_year, appointment->startTime.tm_mon,
          appointment->startTime.tm_mday, appointment->startTime.tm_hour,
          appointment->startTime.tm_min, appointment->endTime.tm_year,
          appointment->endTime.tm_mon, appointment->endTime.tm_mday,
          appointment->endTime.tm_hour, appointment->endTime.tm_min,
          appointment->description);
  fclose(appointments_file);
  free(description);
}

// list all appointments present on appointments.txt, it should parse the file
// that has the following format: YYYY-MM-DD HH:MM~YYYY-MM-DD HH:MM~Description
// display format for dates should be like this:
// Sunday, 15 January 2023 - 23:12
void listAppointments() {
  FILE *appointments_file = fopen("appointments.txt", "r");
  if (appointments_file == NULL) {
    printf("Error: Could not open appointments file\n");
    return;
  }

  char *line = malloc(100);
  while (fgets(line, 100, appointments_file) != NULL) {
    char *start_time = strtok(line, "~");
    char *end_time = strtok(NULL, "~");
    char *description = strtok(NULL, "~");

    struct tm start_time_tm;
    struct tm end_time_tm;

    strptime(start_time, "%Y-%m-%d %H:%M", &start_time_tm);
    strptime(end_time, "%Y-%m-%d %H:%M", &end_time_tm);

    char start_time_str[100];
    char end_time_str[100];

    strftime(start_time_str, 100, "%A, %d %B %Y - %H:%M", &start_time_tm);
    strftime(end_time_str, 100, "%A, %d %B %Y - %H:%M", &end_time_tm);

    printf("start date: %s\n", start_time_str);
    printf("end date: %s\n", end_time_str);
    printf("description: %s\n", description);
  }
  fclose(appointments_file);
  free(line);
}

// do the same of list appointments but only for the month of the given date
void listAppointmentsByMonth(struct tm date) {
  FILE *appointments_file = fopen("appointments.txt", "r");
  if (appointments_file == NULL) {
    printf("Error: Could not open appointments file\n");
    return;
  }

  char *line = malloc(100);
  while (fgets(line, 100, appointments_file) != NULL) {
    char *start_time = strtok(line, "~");
    char *end_time = strtok(NULL, "~");
    char *description = strtok(NULL, "~");

    struct tm start_time_tm;
    struct tm end_time_tm;

    strptime(start_time, "%Y-%m-%d %H:%M", &start_time_tm);
    strptime(end_time, "%Y-%m-%d %H:%M", &end_time_tm);

    if (start_time_tm.tm_mon == date.tm_mon) {
      char start_time_str[100];
      char end_time_str[100];

      strftime(start_time_str, 100, "%A, %d %B %Y - %H:%M", &start_time_tm);
      strftime(end_time_str, 100, "%A, %d %B %Y - %H:%M", &end_time_tm);

      printf("start date: %s\n", start_time_str);
      printf("end date: %s\n", end_time_str);
      printf("description: %s\n", description);
    }
  }
  fclose(appointments_file);
  free(line);
}

// remove an appointment from the file by asking for the index of the line to
// remove from
void removeAppointment() {
  FILE *appointments_file = fopen("appointments.txt", "r");
  if (appointments_file == NULL) {
    printf("Error: Could not open appointments file\n");
    return;
  }

  char *line = malloc(100);
  int line_number = 1;
  while (fgets(line, 100, appointments_file) != NULL) {
    char *start_time = strtok(line, "~");
    char *end_time = strtok(NULL, "~");
    char *description = strtok(NULL, "~");

    struct tm start_time_tm;
    struct tm end_time_tm;

    strptime(start_time, "%Y-%m-%d %H:%M", &start_time_tm);
    strptime(end_time, "%Y-%m-%d %H:%M", &end_time_tm);

    char start_time_str[100];
    char end_time_str[100];

    strftime(start_time_str, 100, "%A, %d %B %Y - %H:%M", &start_time_tm);
    strftime(end_time_str, 100, "%A, %d %B %Y - %H:%M", &end_time_tm);

    printf("%d. start date: %s\n", line_number, start_time_str);
    printf("end date: %s\n", end_time_str);
    printf("description: %s\n", description);
    line_number++;
  }
  fclose(appointments_file);

  printf("Enter the line number to remove: ");
  int line_to_remove;
  scanf("%d", &line_to_remove);

  FILE *new_appointments_file = fopen("new_appointments.txt", "w");
  if (new_appointments_file == NULL) {
    printf("Error: Could not open new appointments file\n");
    return;
  }

  appointments_file = fopen("appointments.txt", "r");
  if (appointments_file == NULL) {
    printf("Error: Could not open appointments file\n");
    return;
  }

  line_number = 1;
  while (fgets(line, 100, appointments_file) != NULL) {
    if (line_number != line_to_remove) {
      fprintf(new_appointments_file, "%s", line);
    }
    line_number++;
  }
  fclose(appointments_file);
  fclose(new_appointments_file);
  remove("appointments.txt");
  rename("new_appointments.txt", "appointments.txt");
  free(line);
}

// update an appointment by asking for the line to update from
// it also should for the name of the field to update and the new value for it
// remember to use appropiate api to time.h fields
void updateAppointment() {
  FILE *appointments_file = fopen("appointments.txt", "r");
  if (appointments_file == NULL) {
    printf("Error: Could not open appointments file\n");
    return;
  }

  char *line = malloc(100);
  int line_number = 1;
  while (fgets(line, 100, appointments_file) != NULL) {
    char *start_time = strtok(line, "~");
    char *end_time = strtok(NULL, "~");
    char *description = strtok(NULL, "~");

    struct tm start_time_tm;
    struct tm end_time_tm;

    strptime(start_time, "%Y-%m-%d %H:%M", &start_time_tm);
    strptime(end_time, "%Y-%m-%d %H:%M", &end_time_tm);

    char start_time_str[100];
    char end_time_str[100];

    strftime(start_time_str, 100, "%A, %d %B %Y - %H:%M", &start_time_tm);
    strftime(end_time_str, 100, "%A, %d %B %Y - %H:%M", &end_time_tm);

    printf("%d. start date: %s\n", line_number, start_time_str);
    printf("end date: %s\n", end_time_str);
    printf("description: %s\n", description);
    line_number++;
  }
  fclose(appointments_file);

  printf("Enter the line number to update: ");
  int line_to_update;
  scanf("%d", &line_to_update);

  FILE *new_appointments_file = fopen("new_appointments.txt", "w");
  if (new_appointments_file == NULL) {
    printf("Error: Could not open new appointments file\n");
    return;
  }

  appointments_file = fopen("appointments.txt", "r");
  if (appointments_file == NULL) {
    printf("Error: Could not open appointments file\n");
    return;
  }

  line_number = 1;
  while (fgets(line, 100, appointments_file) != NULL) {
    if (line_number != line_to_update) {
      fprintf(new_appointments_file, "%s", line);
    } else {
      char *start_time = strtok(line, "~");
      char *end_time = strtok(NULL, "~");
      char *description = strtok(NULL, "~");

      struct tm start_time_tm;
      struct tm end_time_tm;

      strptime(start_time, "%Y-%m-%d %H:%M", &start_time_tm);
      strptime(end_time, "%Y-%m-%d %H:%M", &end_time_tm);

      char start_time_str[100];
      char end_time_str[100];

      strftime(start_time_str, 100, "%A, %d %B %Y - %H:%M", &start_time_tm);
      strftime(end_time_str, 100, "%A, %d %B %Y - %H:%M", &end_time_tm);

      printf("start date: %s\n", start_time_str);
      printf("end date: %s\n", end_time_str);
      printf("description: %s\n", description);

      printf("Enter the field to update (start_time, end_time, description): ");
      char field_to_update[100];
      scanf("%s", field_to_update);

      if (strcmp(field_to_update, "start_time") == 0) {
        printf("Enter the new start time: ");
        char new_start_time[100];
        getchar();
        scanf("%[^\n]s", new_start_time);
        fprintf(new_appointments_file, "%s~%s~%s\n", new_start_time, end_time,
                description);
      } else if (strcmp(field_to_update, "end_time") == 0) {
        printf("Enter the new end time: ");
        char new_end_time[100];
        getchar();
        scanf("%[^\n]s", new_end_time);
        fprintf(new_appointments_file, "%s~%s~%s\n", start_time, new_end_time,
                description);
      } else if (strcmp(field_to_update, "description") == 0) {
        printf("Enter the new description: ");
        char new_description[100];
        getchar();
        scanf("%[^\n]s", new_description);
        fprintf(new_appointments_file, "%s~%s~%s\n", start_time, end_time,
                new_description);
      } else {
        printf("Error: Invalid field to update\n");
        exit(1);
      }
    }
    line_number++;
  }
  fclose(appointments_file);
  fclose(new_appointments_file);
  remove("appointments.txt");
  rename("new_appointments.txt", "appointments.txt");
  free(line);
}

void display_calendar() {
  time_t current_time = time(NULL);
  struct tm *tm = localtime(&current_time);

  int year = tm->tm_year + 1900;
  int month = tm->tm_mon + 1;
  int day = tm->tm_mday;

  int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (month == 2 && year % 4 == 0) {
    if (year % 100 == 0 && year % 400 != 0) {
      days_in_month[2] = 28;
    } else {
      days_in_month[2] = 29;
    }
  }

  printf("Su Mo Tu We Th Fr Sa\n");

  int first_day_of_month = tm->tm_wday - tm->tm_mday % 7;
  if (first_day_of_month < 0) {
    first_day_of_month += 7;
  }

  for (int i = 0; i < first_day_of_month; i++) {
    printf("   ");
  }

  for (int i = 1; i <= days_in_month[month]; i++) {
    if (i == day) {
      printf("\033[1;31m%2d\033[0m ", i);
    } else {
      printf("%2d ", i);
    }

    if ((i + first_day_of_month) % 7 == 0) {
      printf("\n");
    }
  }

  printf("\n\n");
}

void menu() {
  while (1) {
    display_calendar();
    time_t current_time = time(NULL);
    struct tm *tm = localtime(&current_time);
    listAppointmentsByMonth(*tm);
    printf("1. Add appointment\n");
    printf("2. Update appointment\n");
    printf("3. Remove appointment\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    system("clear");
    display_calendar();
    if (choice == 1) {
      struct Appointment appointment;
      createAppointment(&appointment);
    } else if (choice == 2) {
      updateAppointment();
    } else if (choice == 3) {
      removeAppointment();
    } else if (choice == 4) {
      system("clear");
      printf("Goodbye!\n");
      exit(0);
    } else {
      printf("Error: Invalid choice\n");
      exit(1);
    }
    sleep(1);
    system("clear");
  }
}

int main() {
  system("clear");
  createAppointmentsFile();
  menu();
  return 0;
}