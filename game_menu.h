#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <vector>
#include <string>

bool kbhit();
void RestoreInput();
void SetNonBlockingInput();
void PrintGenericMenu(const std::string& title, const std::vector<std::string>& options, int selected, int score);
int ShowGenericMenu(const std::string& title, const std::vector<std::string>& options, int score);
#endif