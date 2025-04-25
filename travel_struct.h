#ifndef TRAVEL_STRUCT_H
#define TRAVEL_STRUCT_H

struct travelMenu
{
  char destination[50];  // Place
  char date[11];         // YYYY-MM-DD
  float expenses;        // How much are you spending
  char description[100]; // On what are you spending
  char category[50];     // Categorize expenses
};

#endif