#include <stdio.h>
#include <stdlib.h>

#include "status.h"
#include "travel_struct.h"
#include "file_utils.h"
#include "input_validation.h"

int btn_0()
{
  struct travelMenu track;

  printf("\nYou are Adding a New Expense\n");
  do
  {
    printf("Add your destination:\n");
    scanf(" %[^\n]", track.destination);
  } while (!isValidString(track.destination));

  do
  {
    printf("Add the date (YYYY-MM-DD):\n");
    scanf(" %[^\n]", track.date);
  } while (!is_valid_date(track.date));

  do
  {
    printf("Add the amount of money you are spending:\n");
    scanf("%f", &track.expenses);
  } while (!isValidValue(&track.expenses));

  getchar(); // Clear the buffer

  do
  {
    printf("Add a small description:\n");
    scanf(" %[^\n]", track.description);
  } while (!isValidString(track.description));

  do
  {
    printf("Add the category of your expense:\n");
    scanf(" %[^\n]", track.category);
  } while (!isValidString(track.category));

  saveInCSV(track, "travel_database.csv");
  return SUCCESS;
}

int btn_1()
{
  char file_name[] = "travel_database.csv";
  FILE *archivo = fopen(file_name, "r"); // just read content, no editing
  if (archivo == NULL)
  {
    printf("An error was produced while trying to open the file.\n");
    return ERROR;
  }

  struct travelMenu track[countLinesInCSV(file_name)];
  int i = 0;

  printf("\n");

  while (fscanf(archivo, "%[^,],%[^,],%f,%[^,],%[^\n]\n",
                track[i].destination,
                track[i].date,
                &track[i].expenses,
                track[i].description,
                track[i].category) == 5)
  {
    printf("Expense number %d\n", i + 1);
    printf("Destination: %s\n", track[i].destination);
    printf("Date: %s\n", track[i].date);
    printf("Expenses: %.2f\n", track[i].expenses);
    printf("Description: %s\n", track[i].description);
    printf("Category: %s\n", track[i].category);

    printf("\n");
    i++;
  }

  fclose(archivo);
  return SUCCESS;
}

int btn_2()
{
  char file_name[] = "travel_database.csv";
  FILE *archivo = fopen(file_name, "r");
  if (archivo == NULL)
  {
    printf("An error was produced while trying to open the file.\n");
    return ERROR;
  }
  struct travelMenu track[countLinesInCSV(file_name)];

  int i = 0;

  // save the data into the struct track variable
  while (fscanf(archivo, "%[^,],%[^,],%f,%[^,],%[^\n]\n",
                track[i].destination,
                track[i].date,
                &track[i].expenses,
                track[i].description,
                track[i].category) == 5)
  {
    i++;
  }

  fclose(archivo);

  int option;
  char choose_edit = '\0';
  printf("Edit your Expenses\n");
  printf("What expense do you want to change? (1, 2, 3, etc..)");
  scanf("%d", &option);
  if (option < 1 || option > i) // Check if option is within the range of expenses
  {
    printf("Invalid option. Returning to the main menu...\n");
    add_error();
    return ERROR;
  }
  option -= 1; // Adjust for 0-based index
  getchar();

  while (choose_edit != 'f')
  {
    printf("What do you want to edit?\n");
    printf("a: Destination\n");
    printf("b: Date\n");
    printf("c: Expenses\n");
    printf("d: Description\n");
    printf("e: category\n");
    printf("f: exit\n");
    scanf(" %c", &choose_edit);

    switch (choose_edit)
    {
    case 'a':
      do
      {
        printf("Edit destination\n");
        scanf(" %[^\n]", track[option].destination);
      } while (!isValidString(track[option].destination));
      break;
    case 'b':
      do
      {
        printf("Edit date\n");
        scanf(" %[^\n]", track[option].date);
      } while (!is_valid_date(track[option].date));
      break;
    case 'c':
      do
      {
        printf("Edit expenses\n");
        scanf("%f", &track[option].expenses);
      } while (!isValidValue(&track[option].expenses));
      break;
    case 'd':
      do
      {
        printf("Edit description\n");
        scanf(" %[^\n]", track[option].description);
      } while (!isValidString(track[option].description));
      break;
    case 'e':
      do
      {
        printf("Edit category\n");
        scanf(" %[^\n]", track[option].category);
      } while (!isValidString(track[option].category));
      break;
    case 'f':
      return 0;
      break;
    default:
      printf("Invalid option. Returning to the main menu...\n");
      add_error();
      break;
    }

    archivo = fopen("travel_database.csv", "w");
    if (archivo == NULL)
    {
      printf("Error writing to the file.\n");
      return ERROR;
    }

    // Write the updated data back to the file
    for (int j = 0; j < i; j++)
    {
      fprintf(archivo, "%s,%s,%.2f,%s,%s\n",
              track[j].destination,
              track[j].date,
              track[j].expenses,
              track[j].description,
              track[j].category);
    }
    fclose(archivo);
  }
  return SUCCESS;
}