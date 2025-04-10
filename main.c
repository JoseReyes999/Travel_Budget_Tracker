#include <stdio.h>
#include <time.h>
#include <string.h>

int num_expens = 0;
int errors = 0; // Counter for errors made

struct travelMenu
{
  char destination[50];  // Place
  char date[11];         // YYYY-MM-DD
  float expenses;        // How much are you spending
  char description[100]; // On what are you spending
  char category[50];     // Categorize expensess
};

void display_menu()
{
  printf("\n0: Add new Expense");
  printf("\n1: View Expenses");
  printf("\n2: Edit Expense");
  printf("\n3: Exit\n");
}

void guardarEnCSV(struct travelMenu track, const char *filename)
{
  FILE *archivo = fopen(filename, "a"); // Modo 'a' para agregar sin borrar
  if (archivo == NULL)
  {
    printf("Error al abrir el archivo.\n");
    return;
  }

  fprintf(archivo, "%s,%s,%.2f,%s,%s\n",
          track.destination,
          track.date,
          track.expenses,
          track.description,
          track.category);

  fclose(archivo);
}

int add_error()
{
  errors++;
  printf("You clicked something incorrect");
}

int btn_0()
{
  struct travelMenu track[100];
  printf("\nYou are Adding a New Expense\n");
  printf("Add your destination:\n");
  scanf(" %[^\n]", track[num_expens].destination);
  printf("Add the date (YYYY-MM-DD)\n");
  scanf(" %[^\n]", track[num_expens].date);
  printf("Add expense:\n");
  scanf("%f", &track[num_expens].expenses);
  getchar(); // Clear the buffer
  printf("Add a small description:\n");
  scanf(" %[^\n]", track[num_expens].description);
  printf("Add the category of your expense:\n");
  scanf(" %[^\n]", track[num_expens].category);

  guardarEnCSV(track[num_expens], "travel_database.csv");
  num_expens++;
  return 1;
}

int btn_1()
{
  FILE *archivo = fopen("travel_database.csv", "r");
  if (archivo == NULL)
  {
    printf("Error al abrir el archivo.\n");
  }

  struct travelMenu track[100];
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
  return 1;
}

int btn_2()
{
  FILE *archivo = fopen("travel_database.csv", "r");
  if (archivo == NULL)
  {
    printf("Error al abrir el archivo.\n");
  }

  struct travelMenu track[100];

  int i = 0;

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
  char choose_edit;
  printf("Edit your Expenses\n");
  printf("What Expense you want to change? (1, 2, 3, etc..)");
  scanf("%d", &option);
  option -= 1; // Adjust for 0-based index
  getchar();

  while (choose_edit != "f")
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
      scanf("%s", track[option].destination);
      break;
    case 'b':
      printf("Edit date\n");
      scanf("%s", track[option].date);
      break;
    case 'c':
      printf("Edit expenses\n");
      scanf("%d", &track[option].expenses);
      break;
    case 'd':
      printf("Edit description\n");
      scanf("%s", track[option].description);
      break;
    case 'e':
      printf("Edit category\n");
      scanf("%s", track[option].category);
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
      return 1;
    }
    printf("%d", i);
    for (int j = 0; j < i; j++)
    {
      printf("%d", i);
      fprintf(archivo, "%s,%s,%.2f,%s,%s\n",
              track[j].destination,
              track[j].date,
              track[j].expenses,
              track[j].description,
              track[j].category);
    }
    fclose(archivo);
  }
  return 1;
}

int main()
{
  int option;

  do
  {

    if (errors == 3)
    {           // Check if errors have reached 3 before continuing
      return 0; // Exit the program
    }

    display_menu(); // This display the menu

    // This makes sure that option is numeric, if it is not numeric gives an error
    if (scanf("%d", &option) != 1)
    {
      // This deletes or cleans the incorrect value
      while (getchar() != "\n")
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
      { // Adds an error
        return 0;
      }
    }
  } while (option != 3);
  return 0;
}