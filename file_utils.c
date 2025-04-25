#include <stdio.h>
#include "file_utils.h"

#include "status.h"

void display_menu()
{
  printf("\n0: Add new Expense");
  printf("\n1: View Expenses");
  printf("\n2: Edit Expense");
  printf("\n3: Exit\n");
}

int countLinesInCSV(const char *filename)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("Failed to open file for counting lines.\n");
    return ERROR;
  }

  int count = 0;
  char ch;
  while ((ch = fgetc(file)) != EOF)
  {
    if (ch == '\n')
    {
      count++;
    }
  }

  fclose(file);
  return count;
}

/*
This function takes in two parameters, a struct travelMenu and a filename.
What this function does is that it will append the structure into the file
*/
int saveInCSV(struct travelMenu track, const char *filename)
{
  FILE *archivo = fopen(filename, "a"); // Mode 'a' to add without deleting existing content
  if (archivo == NULL)
  {
    printf("An error was produced while trying to open the file.\n");
    return ERROR;
  }

  fprintf(archivo, "%s,%s,%.2f,%s,%s\n",
          track.destination,
          track.date,
          track.expenses,
          track.description,
          track.category);

  fclose(archivo);
  return SUCCESS;
}