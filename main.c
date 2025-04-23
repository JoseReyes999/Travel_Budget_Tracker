#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define SUCCESS 1
#define ERROR 0

struct travelMenu
{
  char destination[50];  // Place
  char date[11];         // YYYY-MM-DD
  float expenses;        // How much are you spending
  char description[100]; // On what are you spending
  char category[50];     // Categorize expenses
};

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

/*
This function will handle the amount of wrong inputs done by the user
*/
int add_error()
{
  static int errors = 0; // The function will remember the value every time it is called

  printf("Invalid input. You have %d tries left.\n", 2 - errors);
  errors++;
  if (errors == 3)
  {
    printf("You have made 3 errors, exiting the program...\n");
    return SUCCESS; // Success to satisfy exiting condition in main
  }
  return ERROR;
}

int isValidString(char *str)
{
  if (strchr(str, ',') != NULL)
  {
    printf("Cannot have commas, try again.\n");
    return 0;
  }
  return 1;
}

int is_valid_date(char *date)
{
  if (strlen(date) != 10)
  {
    printf("Invalid date format. Expected YYYY-MM-DD, try again\n");
    return ERROR;
  }
  if (date[4] != '-' || date[7] != '-')
  {
    printf("Make sure you are separating your date with dashes, try again\n");
    return ERROR;
  }

  int year, month, day;
  sscanf(date, "%4d-%2d-%2d", &year, &month, &day); // convert the string into integers and segment into day, month and year

  if (month < 1 || month > 12 || day < 1 || day > 31)
  {
    printf("Invalid month or day values.\n");
    return ERROR;
  }

  return SUCCESS;
}

int isValidValue(float *value)
{
  if (*value <= 0)
  {
    printf("Value cannot be less than or equal to 0, try again\n");
    return 0;
  }
  return 1;
}

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
      printf("Edit destination\n");
      scanf(" %[^\n]", track[option].destination);
      break;
    case 'b':
      printf("Edit date\n");
      scanf(" %[^\n]", track[option].date);
      break;
    case 'c':
      printf("Edit expenses\n");
      scanf(" %[^\n]", &track[option].expenses);
      break;
    case 'd':
      printf("Edit description\n");
      scanf(" %[^\n]", track[option].description);
      break;
    case 'e':
      printf("Edit category\n");
      scanf(" %[^\n]", track[option].category);
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

int main()
{
  int option;

  do
  {

    display_menu(); // This display the menu

    // This makes sure that option is numeric, if it is not numeric gives an error
    if (scanf("%d", &option) != 1)
    {
      // This deletes or cleans the incorrect value
      while (getchar() != '\n')
        ;
      printf("\nInvalid input. Please enter a numeric value.\n");
      add_error(); // This calls the function and adds an error.
      continue;
    }

    switch (option)
    { // In here are the different cases optin can take.
    case 0:
      btn_0();
      break;
    case 1:
      btn_1();
      break;
    case 2:
      btn_2();
      break;
    case 3:
      printf("Exiting the program...\n");
      break;
    default:
      if (add_error())
      {
        return 0;
      }
    }
  } while (option != 3);
  printf("Program exited successfully.\n");
  return 0;
}