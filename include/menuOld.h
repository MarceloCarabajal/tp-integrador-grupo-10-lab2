#ifndef MENU_INCLUDED
#define MENU_INCLUDED

#include <iostream>

#include "rlutil.h"

const int DEFAULT_BG = rlutil::BLACK;

void handleMenu();
void printMenu(int selected);
void printHighlighted(std::string text, bool highlight, int color = 14,
                      int x = 0, int y = 0);

#endif /* MENU_INCLUDED */
