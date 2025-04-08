#include <stdio.h>

int main()
{
  struct travelMenu
  {
    char destination[50];
    char startDate[11]; // YYYY-MM-DD
    char endDate[11];
    float budget;
    float expenses;
    float balance;
  };

  struct expense
  {
    char destination[50];
    char date[11]; // YYYY-MM-DD
    char category[30];
    float amount;
    char note[100];
  };

  return 0;
}