#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "status.h"
#include "file_utils.h"
#include "database_manipulation.h"
#include "input_validation.h"

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
      btn_3();
      break;
    case 4:
      printf("Exiting the program...\n");
      break;
    default:
      add_error();
    }
  } while (option != 4);
  printf("Program exited successfully.\n");
  return 0;
}