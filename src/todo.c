#include "header.h"

void show_todo() {
  struct list td;

  FILE *fp;
  fp = fopen("../data/todolist.txt", "r");

  int line = 1;
  while (fgets(td.list, sizeof(td.list), fp)) {
    printf("%d. %s", line++, td.list);
  }

  fclose(fp);
}

void add_todo() {
  struct list td;

  FILE *fp;
  fp = fopen("../data/todolist.txt", "a");

  printf("Add task: ");
  scanf("%[^\n]", td.list);
  getchar();

  fprintf(fp, "%s\n", td.list);
  fclose(fp);
}

void remove_todo(int line_number) {
  FILE *fp, *temp;
  char ch;
  int current_line = 1;

  fp = fopen("../data/todolist.txt", "r");
  temp = fopen("../data/temp.txt", "w");

  while ((ch = fgetc(fp)) != EOF) {
    if (current_line != line_number) {
      fputc(ch, temp);
    }
    if (ch == '\n')
      current_line++;
  }

  fclose(fp);
  fclose(temp);

  remove("../data/todolist.txt");
  rename("../data/temp.txt", "../data/todolist.txt");
}

void ui_book() {
  char n;
  system("clear");
  printf("1. Add List\n");
  printf("2. See List\n");
  printf("3. Remove List\n");
  n = getchar();
  getchar();

  if (n == 'q')
    return;

  switch (n) {
  case '1':
    system("clear");
    add_todo();
    break;

  case '2':
    system("clear");
    show_todo();
    getchar();
    break;

  case '3':
    system("clear");
    show_todo();
    int line;
    printf("\ndelete/check completed task :");
    scanf("%d", &line);
    getchar();
    remove_todo(line);
    break;

  default:
    break;
  }
  bruh();
}
