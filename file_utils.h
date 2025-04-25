#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "travel_struct.h"

void display_menu();
int saveInCSV(struct travelMenu track, const char *filename);
int countLinesInCSV(const char *filename);

#endif