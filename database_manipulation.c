#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("Add the category of your expense(Food, Emergency, Gift, etc.):\n");
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

  printf("\n1. See everything\n");
  printf("2. See by category\n");
  printf("3. See by date\n");
  printf("4. See by destination\n");

  int option;
  scanf("%d", &option);

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
    i++;
  }

  switch (option)
  {
  case 1:
    for (int j = 0; j < i; j++)
    {
      printf("Expense number %d\n", j + 1);
      printf("Destination: %s\n", track[j].destination);
      printf("Date: %s\n", track[j].date);
      printf("Expenses: %.2f\n", track[j].expenses);
      printf("Description: %s\n", track[j].description);
      printf("Category: %s\n", track[j].category);

      printf("\n");
    }
    break;
  case 2:
  {
    char category[50];
    do
    {
      printf("Enter the category you want to see:\n");
      scanf(" %[^\n]", category);
    } while (!isValidString(category));

    for (int j = 0; j < i; j++)
    {
      if (strcmp(track[j].category, category) == 0)
      {
        printf("Expense number %d\n", j + 1);
        printf("Destination: %s\n", track[j].destination);
        printf("Date: %s\n", track[j].date);
        printf("Expenses: %.2f\n", track[j].expenses);
        printf("Description: %s\n", track[j].description);
        printf("Category: %s\n", track[j].category);

        printf("\n");
      }
    }
    break;
  }
  case 3:
  {
    char date[50];
    do
    {
      printf("Enter the date you want to see:\n");
      scanf(" %[^\n]", date);
    } while (!is_valid_date(date));

    for (int j = 0; j < i; j++)
    {
      if (strcmp(track[j].date, date) == 0)
      {
        printf("Expense number %d\n", j + 1);
        printf("Destination: %s\n", track[j].destination);
        printf("Date: %s\n", track[j].date);
        printf("Expenses: %.2f\n", track[j].expenses);
        printf("Description: %s\n", track[j].description);
        printf("Category: %s\n", track[j].category);

        printf("\n");
      }
    }
    break;
  }
  case 4:
  {
    char destination[50];
    do
    {
      printf("Enter the destination you want to see:\n");
      scanf(" %[^\n]", destination);
    } while (!isValidString(destination));

    for (int j = 0; j < i; j++)
    {
      if (strcmp(track[j].destination, destination) == 0)
      {
        printf("Expense number %d\n", j + 1);
        printf("Destination: %s\n", track[j].destination);
        printf("Date: %s\n", track[j].date);
        printf("Expenses: %.2f\n", track[j].expenses);
        printf("Description: %s\n", track[j].description);
        printf("Category: %s\n", track[j].category);

        printf("\n");
      }
    }
    break;
  }
  default:
    break;
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
  printf("\n");

  // save the data into the struct track variable
  while (fscanf(archivo, "%[^,],%[^,],%f,%[^,],%[^\n]\n",
                track[i].destination,
                track[i].date,
                &track[i].expenses,
                track[i].description,
                track[i].category) == 5)
  {
    printf("%d. $%.2f for %s in %s (%s, %s)\n", i + 1, track[i].expenses, track[i].description, track[i].destination, track[i].date, track[i].category);
    i++;
  }

  fclose(archivo);

  int option;
  char choose_edit = '\0';
  printf("\nEdit your Expenses\n");
  printf("What expense do you want to change? (1, 2, 3, etc..)\n");
  scanf("%d", &option);
  if (option < 1 || option > i) // Check if option is within the range of expenses
  {
    printf("Invalid option. Returning to the main menu...\n");
    add_error();
    getchar(); // Clear the buffer
    return ERROR;
  }
  option -= 1; // Adjust for 0-based index
  getchar();

  while (choose_edit != 'f')
  {
    printf("What do you want to edit?\n");
    printf("a: Destination\n");
    printf("b: Date\n");
    printf("c: Price\n");
    printf("d: Description\n");
    printf("e: category\n");
    printf("f: exit\n");
    scanf(" %c", &choose_edit);

    switch (choose_edit)
    {
    case 'a':
      do
      {
        printf("Edit destination(You had: %s)\n", track[option].destination);
        scanf(" %[^\n]", track[option].destination);
        printf("Successfully changed destination of expense number %d to %s\n", i + 1, track[option].destination);
      } while (!isValidString(track[option].destination));
      break;
    case 'b':
      do
      {
        printf("Edit date(You had %s)\n", track[option].date);
        scanf(" %[^\n]", track[option].date);
        printf("Successfully changed date of expense number %d to %s\n", i + 1, track[option].date);
      } while (!is_valid_date(track[option].date));
      break;
    case 'c':
      do
      {
        printf("Edit expenses(You had $%.2f)\n", track[option].expenses);
        scanf("%f", &track[option].expenses);
        printf("Successfully changed price of expense number %d to $%.2f\n", i + 1, track[option].expenses);
      } while (!isValidValue(&track[option].expenses));
      break;
    case 'd':
      do
      {
        printf("Edit description(You had %s)\n", track[option].description);
        scanf(" %[^\n]", track[option].description);
        printf("Successfully changed description of expense number %d to %s\n", i + 1, track[option].description);
      } while (!isValidString(track[option].description));
      break;
    case 'e':
      do
      {
        printf("Edit category(You had %s)\n", track[option].category);
        scanf(" %[^\n]", track[option].category);
        printf("Successfully changed category of expense number %d to %s\n", i + 1, track[option].category);
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
  getchar(); // Clear the buffer
  return SUCCESS;
}