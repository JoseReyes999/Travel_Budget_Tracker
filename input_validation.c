#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "input_validation.h"

#include "status.h"

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
    // return SUCCESS; // Success to satisfy exiting condition in main
    exit(EXIT_FAILURE);
  }
  return ERROR;
}

int isValidString(char *str)
{
  if (strchr(str, ',') != NULL)
  {
    printf("Cannot have commas, try again.\n");
    return ERROR;
  }
  return SUCCESS;
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
    return ERROR;
  }
  return SUCCESS;
}