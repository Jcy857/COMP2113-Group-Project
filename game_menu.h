#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <vector>
#include <string>

bool kbhit();
void restoreInput();
void setNonBlockingInput();
void printGenericMenu(const std::string& title, const std::vector<std::string>& options, int selected, int score);
int showGenericMenu(const std::string& title, const std::vector<std::string>& options, int score);
#endif