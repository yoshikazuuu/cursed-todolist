#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __USE_XOPEN
#include <time.h>

struct Appointment {
  struct tm startTime;
  struct tm endTime;
  char *description;
};

int validateTime(struct tm *time) {
  if (time->tm_year < 1900 || time->tm_year > 2100) {
    printf("Invalid year\n");
    return 0;
  }
  if (time->tm_mon < 1 || time->tm_mon > 12) {
    printf("Invalid month\n");
    return 0;
  }
  if (time->tm_mday < 1 || time->tm_mday > 31) {
    printf("Invalid day\n");
    return 0;
  }
  if (time->tm_hour < 0 || time->tm_hour > 23) {
    printf("Invalid hour\n");
    return 0;
  }
  if (time->tm_min < 0 || time->tm_min > 59) {
    printf("Invalid minute\n");
    return 0;
  }
  return 1;
}

void createAppointment(struct Appointment *appointment) {
  FILE *fp = fopen("appointments.txt", "a");
  if (fp == NULL) {
    printf("Error opening file\n");
    return;
  }

  printf("Enter start time (YYYY-MM-DD HH:MM): ");
  scanf("%d-%d-%d %d:%d", &appointment->startTime.tm_year,
        &appointment->startTime.tm_mon, &appointment->startTime.tm_mday,
        &appointment->startTime.tm_hour, &appointment->startTime.tm_min);
  getchar();

  if (!validateTime(&appointment->startTime)) {
    return;
  }

  printf("Enter end time (YYYY-MM-DD HH:MM): ");
  scanf("%d-%d-%d %d:%d", &appointment->endTime.tm_year,
        &appointment->endTime.tm_mon, &appointment->endTime.tm_mday,
        &appointment->endTime.tm_hour, &appointment->endTime.tm_min);
  getchar();

  if (!validateTime(&appointment->endTime)) {
    return;
  }

  if (mktime(&appointment->startTime) > mktime(&appointment->endTime)) {
    printf("End time must be after start time\n");
    return;
  }

  char *description = malloc(100);
  printf("Enter description: ");
  fgets(description, 100, stdin);
  getchar();
  appointment->description = description;

  fprintf(fp, "%d-%d-%d %d:%d %d-%d-%d %d:%d %s\n",
          appointment->startTime.tm_year, appointment->startTime.tm_mon,
          appointment->startTime.tm_mday, appointment->startTime.tm_hour,
          appointment->startTime.tm_min, appointment->endTime.tm_year,
          appointment->endTime.tm_mon, appointment->endTime.tm_mday,
          appointment->endTime.tm_hour, appointment->endTime.tm_min,
          appointment->description);

  free(description);

  fclose(fp);
}

void listAppointments() {
  FILE *fp = fopen("appointments.txt", "r");
  if (fp == NULL) {
    printf("Error opening file\n");
    return;
  }

  char *line = malloc(100);
  while (fgets(line, 100, fp) != NULL) {
    printf("%s", line);
  }

  free(line);
  fclose(fp);

  return;
}

void deleteAppointment() {
  FILE *fp = fopen("appointments.txt", "r");
  if (fp == NULL) {
    printf("Error opening file\n");
    return;
  }

  int lineCount = 0;
  char *line = malloc(100);
  while (fgets(line, 100, fp) != NULL) {
    lineCount++;
  }
  free(line);
  fclose(fp);

  char **lines = malloc(lineCount * sizeof(char *));
  fp = fopen("appointments.txt", "r");
  for (int i = 0; i < lineCount; i++) {
    lines[i] = malloc(100);
    fgets(lines[i], 100, fp);
  }
  fclose(fp);

  for (int i = 0; i < lineCount; i++) {
    printf("%d. %s", i + 1, lines[i]);
  }

  int lineNumber;
  printf("\nEnter line number to delete: ");
  scanf("%d", &lineNumber);
  getchar();

  free(lines[lineNumber - 1]);
  for (int i = lineNumber - 1; i < lineCount - 1; i++) {
    lines[i] = lines[i + 1];
  }

  fp = fopen("appointments.txt", "w");
  for (int i = 0; i < lineCount - 1; i++) {
    fprintf(fp, "%s", lines[i]);
  }
  fclose(fp);

  free(lines);
}

// ! FOR TESTING PURPOSES ONLY
int main() {
  struct Appointment appointment;
  int choice;
  while (1) {
    printf("1. Create appointment\n");
    printf("2. List appointments\n");
    printf("3. Delete appointment\n");
    printf("4. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      createAppointment(&appointment);
      break;
    case 2:
      listAppointments();
      break;
    case 3:
      deleteAppointment();
      break;
    case 4:
      return 0;
    default:
      printf("Invalid choice\n");
    }
  }
}
